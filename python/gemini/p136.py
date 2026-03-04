from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod')
def check_mod():
    # Extracting parameters from the URL query string
    username = request.args.get('username')
    password = request.args.get('password')
    
    # Logic to verify credentials (simplified)
    if username == "admin" and password == "secret123":
        return "true"
    return "false"

if __name__ == '__main__':
    app.run()