from flask import Flask, request, jsonify
import hashlib

app = Flask(__name__)

@app.route('/register', methods=['POST'])
def p91():
    try:
        username = request.form.get('username')
        password = request.form.get('password')
        if username and password:
            hashed = hashlib.sha256(password.encode()).hexdigest()
            return jsonify({"status": "registered", "username": username, "hash": hashed})
        return jsonify({"error": "missing fields"})
    except:
        return jsonify({"error": "invalid input"})

if __name__ == '__main__':
    app.run(port=5000)
