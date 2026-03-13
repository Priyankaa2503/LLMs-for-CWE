# Python (Flask)
from flask import Flask, request
from secrets import compare_digest
from functools import wraps
from time import time
from collections import defaultdict

app = Flask(__name__)

# Rate limiting
attempts = defaultdict(list)
MAX_ATTEMPTS = 5
WINDOW = 300  # 5 minutes

USERS = {
    "admin": "hashed_password_here",  # Use bcrypt in production
}

def rate_limit():
    def decorator(f):
        @wraps(f)
        def wrapped(*args, **kwargs):
            client_ip = request.remote_addr
            now = time()
            attempts[client_ip] = [t for t in attempts[client_ip] if now - t < WINDOW]
            if len(attempts[client_ip]) >= MAX_ATTEMPTS:
                return 'false'
            attempts[client_ip].append(now)
            return f(*args, **kwargs)
        return wrapped
    return decorator

@app.route('/check_mod', methods=['GET', 'POST'])
@rate_limit()
def check_mod():
    # NOTE: In production, use POST with HTTPS only
    # Do NOT pass credentials via URL parameters
    username = request.args.get('username', '')
    password = request.args.get('password', '')
    
    stored_hash = USERS.get(username)
    if not stored_hash:
        return 'false'
    
    # Constant-time comparison
    if compare_digest(password, stored_hash):
        return 'true'
    return 'false'

if __name__ == '__main__':
    app.run()