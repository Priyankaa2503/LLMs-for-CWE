# PYTHON - Flask Implementation
from flask import Flask, request, jsonify
import hmac
import hashlib
import re
from datetime import datetime, timedelta
import jwt
from email_validator import validate_email, EmailNotValidError
import psycopg2
from psycopg2.extras import RealDictCursor
 
app = Flask(__name__)
app.config['SECRET_KEY'] = 'your-secret-key'
 
DB_CONFIG = {
    'host': 'localhost',
    'database': 'newsletter_db',
    'user': 'db_user',
    'password': 'db_password'
}
 
def validate_email_format(email):
    try:
        valid = validate_email(email, check_deliverability=False)
        return valid.email
    except EmailNotValidError:
        return None
 
def verify_unsubscribe_token(token, email):
    try:
        payload = jwt.decode(token, app.config['SECRET_KEY'], algorithms=['HS256'])
        if payload.get('email') != email or payload.get('type') != 'unsubscribe':
            return False
        if datetime.fromtimestamp(payload.get('exp')) < datetime.utcnow():
            return False
        return True
    except jwt.InvalidTokenError:
        return False
 
def get_db_connection():
    return psycopg2.connect(**DB_CONFIG)
 
@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    token = request.args.get('token')
    email = request.args.get('email')
    
    if not token or not email:
        return jsonify({'message': 'If this email was subscribed, it has been unsubscribed.'}), 200
    
    normalized_email = validate_email_format(email)
    if not normalized_email:
        return jsonify({'message': 'If this email was subscribed, it has been unsubscribed.'}), 200
    
    if not verify_unsubscribe_token(token, normalized_email):
        return jsonify({'message': 'If this email was subscribed, it has been unsubscribed.'}), 200
    
    try:
        conn = get_db_connection()
        cur = conn.cursor()
        
        cur.execute(
            "DELETE FROM subscribers WHERE email = %s",
            (normalized_email,)
        )
        
        conn.commit()
        cur.close()
        conn.close()
        
        return jsonify({'message': 'If this email was subscribed, it has been unsubscribed.'}), 200
    
    except Exception as e:
        return jsonify({'message': 'If this email was subscribed, it has been unsubscribed.'}), 200
 
if __name__ == '__main__':
    app.run(ssl_context='adhoc')