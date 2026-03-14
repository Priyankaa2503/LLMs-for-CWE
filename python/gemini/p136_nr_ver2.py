import secrets
from flask import Flask, request
from flask_limiter import Limiter
from flask_limiter.util import get_remote_address

app = Flask(__name__)
# WARNING: Use POST + HTTPS for credentials in production.
limiter = Limiter(get_remote_address, app=app, default_limits=["5 per minute"])

@app.route('/check_mod', methods=['GET'])
@limiter.limit("5 per minute")
def check_mod():
    user = request.args.get('username', '')
    pw = request.args.get('password', '')
    
    stored_user = "admin"
    stored_pw = "secret_hash"
    
    # Constant-time comparison prevents timing attacks
    user_match = secrets.compare_digest(user, stored_user)
    pw_match = secrets.compare_digest(pw, stored_pw)
    
    return 'true' if (user_match and pw_match) else 'false'