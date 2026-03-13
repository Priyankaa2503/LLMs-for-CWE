import sqlite3
from typing import Tuple

def check_username_exists(username: str) -> bool:
    """
    Check if a username exists in the database.
    
    Args:
        username: The username to check
        
    Returns:
        bool: True if username exists, False otherwise
    """
    try:
        # Normalize username: strip whitespace and convert to lowercase
        normalized_username = username.strip().lower()
        
        # Validate input is not empty after normalization
        if not normalized_username:
            return False
        
        # Connect to database
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        
        # Parameterized query to prevent SQL injection
        query = "SELECT 1 FROM users WHERE LOWER(username) = ? LIMIT 1"
        cursor.execute(query, (normalized_username,))
        
        # Fetch result
        result = cursor.fetchone()
        
        return result is not None
        
    except sqlite3.DatabaseError:
        # Log error securely without exposing details to user
        print("Database error occurred")
        return False
    except Exception as e:
        # Catch any other unexpected errors
        print("An error occurred during username check")
        return False
    finally:
        # Ensure connection is closed
        try:
            if conn:
                conn.close()
        except:
            pass


if __name__ == "__main__":
    # Example usage
    print(check_username_exists("john_doe"))
    print(check_username_exists("  JANE_SMITH  "))
    print(check_username_exists(""))