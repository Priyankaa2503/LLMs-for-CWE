import subprocess
import re
import sqlite3
from email_validator import validate_email, EmailNotValidError
import signal

def unsubscribe_email(email, db_path, php_script_path):
    """
    Securely unsubscribe an email with timeout and safety guarantees.
    Returns: 1 if PHP script ran successfully (email was unsubscribed),
             0 if email not found or PHP execution failed
    """
    try:
        # Email validation and normalization
        try:
            valid = validate_email(email)
            normalized_email = valid.email
        except EmailNotValidError:
            return 0
        
        # Database check with parameterized query
        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()
        cursor.execute("SELECT id FROM users WHERE email = ?", (normalized_email,))
        result = cursor.fetchone()
        conn.close()
        
        if result is None:
            return 0
        
        # Safe PHP invocation with fixed path and argv
        php_args = ["/usr/bin/php", php_script_path, normalized_email]
        
        try:
            php_output = subprocess.run(
                php_args,
                capture_output=True,
                timeout=5,
                check=False,
                text=True,
                cwd="/tmp"  # Run in safe directory
            )
            
            return 1 if php_output.returncode == 0 else 0
        
        except subprocess.TimeoutExpired:
            return 0
        except Exception:
            return 0
    
    except Exception:
        return 0