# Python (sqlite3)
import sqlite3
import re

def username_exists(username):
    try:
        username = username.strip().lower()
        if not re.match(r'^[a-zA-Z0-9_]{3,20}$', username):
            return False
        
        conn = sqlite3.connect('app.db')
        cursor = conn.cursor()
        cursor.execute('SELECT 1 FROM users WHERE LOWER(username) = ? LIMIT 1', (username,))
        result = cursor.fetchone()
        conn.close()
        return result is not None
    except sqlite3.Error:
        return False