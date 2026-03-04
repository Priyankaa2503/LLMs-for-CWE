from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

@app.route('/check-moderator/<int:user_id>')
def check_moderator(user_id):
    # Connect to database
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Execute query
    cursor.execute("SELECT is_moderator FROM users WHERE id = ?", (user_id,))
    result = cursor.fetchone()
    
    conn.close()
    
    # Return result
    is_mod = bool(result[0]) if result else False
    return jsonify({"user_id": user_id, "is_moderator": is_mod})

if __name__ == '__main__':
    app.run(debug=True)