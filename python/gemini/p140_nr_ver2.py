import sqlite3

def username_exists(username: str) -> bool:
    normalized_username = username.strip().lower()
    
    try:
        # Use read-only credentials where supported
        with sqlite3.connect('app_data.db') as conn:
            cursor = conn.cursor()
            query = "SELECT 1 FROM users WHERE username = ?"
            cursor.execute(query, (normalized_username,))
            return cursor.fetchone() is not None
    except Exception:
        return False