from flask import Flask, request, jsonify
import hashlib
import os

app = Flask(__name__)

@app.route('/register', methods=['POST'])
def p95():
    username = request.form.get('username')
    password = request.form.get('password')
    if username and password:
        salt = os.urandom(16).hex()
        hashed = hashlib.sha256((password + salt).encode()).hexdigest()
        combined = hashed + salt
        return jsonify({"registered": True, "salt": salt, "combined": combined})
    return jsonify({"registered": False})

if __name__ == '__main__':
    app.run(port=5000)
