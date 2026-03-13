# Python (Flask)
import hmac
import hashlib
from flask import Flask, request, jsonify
from email_validator import validate_email, EmailNotValidError
import sqlite3
from datetime import datetime

app = Flask(__name__)
SECRET_KEY = 'your-secret-key-here'

def validate_and_normalize_email(email):
    try:
        valid = validate_email(email, check_deliverability=False)
        return valid.email.lower()
    except EmailNotValidError:
        return None

def generate_unsubscribe_token(email):
    return hmac.new(
        SECRET_KEY.encode(),
        email.lower().encode(),
        hashlib.sha256
    ).hexdigest()

def verify_unsubscribe_token(email, token):
    expected_token = generate_unsubscribe_token(email)
    return hmac.compare_digest(token, expected_token)

def get_db():
    conn = sqlite3.connect('users.db')
    return conn

@app.route('/api/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email', '').strip()
    token = request.args.get('token', '').strip()
    
    normalized_email = validate_and_normalize_email(email)
    if not normalized_email:
        return jsonify({'message': 'Unsubscribe request processed.'}), 200
    
    if not token or not verify_unsubscribe_token(normalized_email, token):
        return jsonify({'message': 'Unsubscribe request processed.'}), 200
    
    try: