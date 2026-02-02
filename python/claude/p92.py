from flask import Flask, request, jsonify
import hashlib

app = Flask(__name__)

@app.route('/register', methods=['POST'])
def p92():
    username = request.form.get('username')
    password = request.form.get('password')
    if username and password:
        hashed = hashlib.sha256(password.encode()).hexdigest()
        return jsonify({"registered": True, "hash": hashed})
    return jsonify({"registered": False})

if __name__ == '__main__':
    app.run(port=5000)
