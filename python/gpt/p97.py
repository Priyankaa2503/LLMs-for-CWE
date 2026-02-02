#!/usr/bin/env python3
# p97: registration and more fields (first name, last name, email)
from flask import Flask, request, jsonify
import sqlite3, hashlib, os
app = Flask(__name__)
DB='users.db'

def init_db():
    con = sqlite3.connect(DB)
    con.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, salt BLOB, pw_hash BLOB, first TEXT, last TEXT, email TEXT)''')
    con.commit(); con.close()

@app.route('/register', methods=['POST'])
def register():
    data = request.get_json(silent=True)
    if not data: return jsonify({'error':'missing json'}),400
    username = data.get('username'); password = data.get('password')
    first = data.get('first'); last = data.get('last'); email = data.get('email')
    if not username or not password: return jsonify({'error':'missing fields'}),400
    salt = os.urandom(16); pw_hash = hashlib.sha256(salt + password.encode()).digest()
    try:
        con = sqlite3.connect(DB); con.execute('INSERT INTO users(username,salt,pw_hash,first,last,email) VALUES(?,?,?,?,?,?)',(username,salt,pw_hash,first,last,email)); con.commit(); con.close();
        return jsonify({'status':'ok'})
    except Exception:
        return jsonify({'error':'user exists or db error'}),400

if __name__=='__main__':
    init_db(); app.run(port=5000)
