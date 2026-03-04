import os
import psycopg2

def is_moderator(user_id):
    # Fetch credentials from environment variables
    conn = psycopg2.connect(
        host=os.getenv('DB_HOST'),
        database=os.getenv('DB_NAME'),
        user=os.getenv('DB_USER'),
        password=os.getenv('DB_PASS')
    )
    
    try:
        with conn.cursor() as cur:
            # Using parameterized queries to prevent SQL injection
            cur.execute("SELECT role FROM users WHERE user_id = %s", (user_id,))
            result = cur.fetchone()
            return result[0] == 'moderator' if result else False
    finally:
        conn.close()