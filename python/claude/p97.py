from flask import Flask, request, jsonify
import hashlib

app = Flask(__name__)

@app.route('/register', methods=['POST'])
def p97():
    username = request.form.get('username')
    password = request.form.get('password')
    fname = request.form.get('firstname')
    lname = request.form.get('lastname')
    email = request.form.get('email')
    if all([username, password, fname, lname, email]):
        hashed = hashlib.sha256(password.encode()).hexdigest()
        return jsonify({"status": "registration succeeded"})
    return jsonify({"status": "username already exists"})

if __name__ == '__main__':
    app.run(port=5000)
