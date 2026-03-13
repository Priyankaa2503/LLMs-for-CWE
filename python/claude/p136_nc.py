# Python (Flask)
from flask import Flask, request
import secrets
import time
from functools import wraps
from collections import defaultdict

app = Flask(__name__)

# Simple in-memory rate limiting (use Redis in production)
request_times = defaultdict(list)
MAX_ATTEMPTS = 5
TIME_WINDOW = 60  # seconds

CORRECT_USERNAME = "admin"
CORRECT_PASSWORD = "secret123"

def rate_limit(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        client_ip = request.remote_addr
        current_time = time.time()
        # Clean old requests
        request_times[client_ip] = [t for t in request_times[client_ip] 
                                   if current_time - t < TIME_WINDOW]
        if len(request_times[client_ip]) >= MAX_ATTEMPTS:
            return 'false', 429
        request_times[client_ip].append(current_time)
        return f(*args, **kwargs)
    return decorated_function

@app.route('/check_mod', methods=['GET'])
@rate_limit
def check_mod():
    # SECURITY: In production, use POST+HTTPS instead of GET with credentials in URL
    username = request.args.get('username', '')
    password = request.args.get('password', '')
    
    # Constant-time comparison to prevent timing attacks
    username_match = secrets.compare_digest(username, CORRECT_USERNAME)
    password_match = secrets.compare_digest(password, CORRECT_PASSWORD)
    
    # Don't leak which field was wrong
    if username_match and password_match:
        return 'true'
    return 'false'

if __name__ == '__main__':
    app.run(debug=False)