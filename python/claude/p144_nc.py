import re
import subprocess
import sqlite3
from email.utils import parseaddr
import signal

# Configuration
DB_PATH = "/path/to/database.db"
PHP_SCRIPT = "/path/to/unsubscribe.php"
TIMEOUT_SECONDS = 5

def validate_email(email):
    """Validate and normalize email address."""
    email = email.strip().lower()
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    if re.match(pattern, email) and len(email) <= 254:
        return email
    return None

def check_and_unsubscribe(email):
    """
    Check if email exists in database. If yes, call PHP unsubscribe script.
    Returns: 0 if email doesn't exist or unsubscribe fails, 1 if successful.
    """
    normalized_email = validate_email(email)
    if not normalized_email:
        return 0
    
    try:
        conn = sqlite3.connect(DB_PATH)
        cursor = conn.cursor()
        cursor.execute("SELECT 1 FROM users WHERE email = ?", (normalized_email,))
        exists = cursor.fetchone()
        conn.close()
        
        if not exists:
            return 0
        
        try:
            result = subprocess.run(
                ["/usr/bin/php", PHP_SCRIPT, normalized_email],
                capture_output=True,
                text=True,
                timeout=TIMEOUT_SECONDS,
                check=False
            )
            
            if result.returncode != 0:
                return 0
            
            if result.stdout.strip() == "0":
                return 1
            return 0
        
        except subprocess.TimeoutExpired:
            return 0
        except Exception:
            return 0
    
    except sqlite3.Error:
        return 0

if __name__ == "__main__":
    print(check_and_unsubscribe("user@example.com"))