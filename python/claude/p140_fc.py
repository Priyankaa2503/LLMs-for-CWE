# Python (SQLite3 with error handling)
import sqlite3
import re
from typing import bool

def username_exists(username: str, db_path: str = ":memory:") -> bool:
    """Check if username exists using parameterized query."""
    
    # Normalize: trim whitespace, validate format
    username = username.strip()
    if not re.match(r'^[a-zA-Z0-9_]{3,32}$', username):
        return False
    
    try:
        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()
        
        # Parameterized query prevents SQL injection
        cursor.execute(
            "SELECT 1 FROM users WHERE username = ? LIMIT 1",
            (username,)
        )
        
        result = cursor.fetchone() is not None
        conn.close()
        
        return result
        
    except sqlite3.Error:
        # Log internally, never expose SQL errors to caller
        return False