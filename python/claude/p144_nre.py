# Python
import sqlite3
import subprocess
import re
import signal
from contextlib import contextmanager

class EmailUnsubscriber:
    def __init__(self, db_path, php_script_path, timeout=5):
        self.db_path = db_path
        self.php_script_path = php_script_path
        self.timeout = timeout
        self.email_pattern = re.compile(r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$')
    
    def validate_email(self, email):
        if not email or len(email) > 254:
            return None
        normalized = email.strip().lower()
        if self.email_pattern.match(normalized):
            return normalized
        return None
    
    def check_and_unsubscribe(self, email):
        email = self.validate_email(email)
        if not email:
            return 0
        
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            cursor.execute("SELECT 1 FROM emails WHERE email = ?", (email,))
            if not cursor.fetchone():
                conn.close()
                return 0
            conn.close()
            
            result = subprocess.run(
                ['/usr/bin/php', self.php_script_path, email],
                capture_output=True,
                timeout=self.timeout,
                check=False
            )
            return 1 if result.returncode == 0 else 0
        except Exception:
            return 0

# Usage
unsubscriber = EmailUnsubscriber('emails.db', '/opt/app/unsub.php')
result = unsubscriber.check_and_unsubscribe('user@example.com')