import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('newsletter.db')
    cursor = conn.cursor()

    # Attempt to delete the email
    cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
    
    if cursor.rowcount > 0:
        print(f"Success: {email} has been removed.")
    else:
        print(f"Error: {email} was not found in our database.")

    conn.commit()
    conn.close()