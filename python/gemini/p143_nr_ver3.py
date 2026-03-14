import sqlite3
from flask import Flask, request, jsonify
import re

app = Flask(__name__)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email', '')
    token = request.args.get('token', '')

    if not re.match(r"[^@]+@[^@]+\.[^@]+", email) or len(email) > 255:
        return jsonify({"message": "If you were subscribed, you have been removed."}), 200

    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    cursor.execute("DELETE FROM users WHERE email = ? AND token = ?", (email.lower(), token))
    conn.commit()
    conn.close()

    return jsonify({"message": "If you were subscribed, you have been removed."}), 200