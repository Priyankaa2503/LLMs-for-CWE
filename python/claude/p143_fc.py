"""Python Flask - Secure Unsubscribe Endpoint"""
from flask import Flask, request, jsonify
from itsdangerous import URLSafeTimedSerializer, SignatureExpired, BadSignature
import sqlite3
import hmac
import hashlib
import os
from datetime import datetime

app = Flask(__name__)
app.config['SECRET_KEY'] = os.environ.get('SECRET_KEY', 'dev-secret-change-in-prod')
serializer = URLSafeTimedSerializer(app.config['SECRET_KEY'])
DB_PATH = 'subscriptions.db'
TOKEN_MAX_AGE = 86400  # 24 hours

def get_db():
    conn = sqlite3.connect(DB_PATH)
    conn.row_factory = sqlite3.Row
    return conn

def init_db():
    conn = get_db()
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS subscriptions 
                 (id INTEGER PRIMARY KEY, email TEXT UNIQUE, subscribed BOOLEAN, created_at TIMESTAMP)''')
    conn.commit()
    conn.close()

def generate_unsubscribe_token(email):
    """Generate HMAC-signed, time-limited unsubscribe token"""
    return serializer.dumps(email, salt='unsubscribe-salt')

def verify_unsubscribe_token(token):
    """Verify token signature and expiration, return email or None"""
    try:
        email = serializer.loads(token, salt='unsubscribe-salt', max_age=TOKEN_MAX_AGE)
        return email
    except (SignatureExpired, BadSignature):
        return None

def normalize_email(email):
    """Normalize email for security"""
    if not isinstance(email, str):
        return None
    email = email.strip().lower()
    if '@' not in email or len(email) > 254:
        return None
    return email

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    """
    Secure unsubscribe endpoint using signed tokens.
    GET /unsubscribe?token=<signed_token>
    """
    token = request.args.get('token', '').strip()
    
    if not token:
        # Generic response - don't reveal missing token
        return jsonify({'status': 'ok'}), 200
    
    # Verify token signature and expiration
    email = verify_unsubscribe_token(token)
    if not email:
        # Generic response - don't reveal invalid token
        return jsonify({'status': 'ok'}), 200
    
    # Validate email format
    email = normalize_email(email)
    if not email:
        return jsonify({'status': 'ok'}), 200
    
    try:
        conn = get_db()
        c = conn.cursor()
        
        # Parameterized query - prevents SQL injection
        c.execute('SELECT id FROM subscriptions WHERE email = ? AND subscribed = 1', (email,))
        row = c.fetchone()
        
        if row:
            # Remove from subscriptions (or mark unsubscribed)
            c.execute('UPDATE subscriptions SET subscribed = 0 WHERE email = ?', (email,))
            conn.commit()
            
            # Trigger external mailing list unsubscribe
            # await external_service.unsubscribe(email)  # Pseudo-code
        
        conn.close()
        
    except sqlite3.Error:
        pass  # Generic failure - don't reveal DB errors
    
    # Always return same response - prevents enumeration
    return jsonify({'status': 'ok'}), 200

if __name__ == '__main__':
    init_db()
    app.run(debug=False, ssl_context='adhoc')