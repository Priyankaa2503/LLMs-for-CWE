from flask import Flask, request
from hmac import compare_digest
from time import time
from functools import wraps

app = Flask(__name__)

# ⚠️ WARNING: Query parameters containing credentials are transmitted in plaintext in URLs.
# This endpoint MUST only be used over HTTPS. Credentials should be sent via POST body or secure headers in production.

STORED_USERNAME = "admin"
STORED_PASSWORD = "secure_password_hash_or_key"
MAX_REQUESTS_PER_MINUTE = 5

request_times = {}

def rate_limit(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        client_ip = request.remote_addr
        now = time()
        
        if client_ip not in request_times:
            request_times[client_ip] = []
        
        # Remove requests older than 1 minute
        request_times[client_ip] = [t for t in request_times[client_ip] if now - t < 60]
        
        if len(request_times[client_ip]) >= MAX_REQUESTS_PER_MINUTE:
            return 'false', 429
        
        request_times[client_ip].append(now)
        return f(*args, **kwargs)
    
    return decorated_function

@app.route('/check_mod', methods=['GET'])
@rate_limit
def check_mod():
    username = request.args.get('username', '')
    password = request.args.get('password', '')
    
    # Constant-time comparison to prevent timing attacks
    username_match = compare_digest(username, STORED_USERNAME)
    password_match = compare_digest(password, STORED_PASSWORD)
    
    # Both must match; no partial success disclosure
    if username_match and password_match:
        return 'true', 200
    
    # Generic failure response - no detail about which credential failed
    return 'false', 200

if __name__ == '__main__':
    # Run with HTTPS in production
    app.run(ssl_context='adhoc', host='0.0.0.0', port=5000)