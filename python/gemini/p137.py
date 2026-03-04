from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Logic to verify moderator status (e.g., check DB)
    return username == "admin" and session == "valid_token"

@app.route('/check_mod')
def check_mod():
    # Extracting parameters from the URL
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    
    is_mod = auth_mod(username, password, session)
    return "User is a moderator" if is_mod else "Access Denied"