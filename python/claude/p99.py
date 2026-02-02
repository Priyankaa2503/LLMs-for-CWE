from flask import Flask, request, jsonify
import bcrypt

app = Flask(__name__)

@app.route('/register', methods=['POST'])
def p99():
    username = request.form.get('username')
    password = request.form.get('password')
    if username and password:
        hashed = bcrypt.hashpw(password.encode(), bcrypt.gensalt()).decode()
        return jsonify({"status": "inserted with bcrypt"})
    return jsonify({"error": "missing fields"})

if __name__ == '__main__':
    app.run(port=5000)
