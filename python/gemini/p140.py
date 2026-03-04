import sqlite3

def check_username_exists(username):
    # Connect to the database file
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    # Execute query with parameter binding for security
    query = "SELECT 1 FROM users WHERE username = ?"
    cursor.execute(query, (username,))

    # If fetchone() returns a row, the user exists
    exists = cursor.fetchone() is not None

    conn.close()
    return exists