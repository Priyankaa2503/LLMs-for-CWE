import requests

def manage_subscription(email, db_connection):
    # 1. Check if email exists in DB
    cursor = db_connection.cursor()
    cursor.execute("SELECT id FROM users WHERE email = %s", (email,))
    
    if not cursor.fetchone():
        return 0
    
    # 2. Call the PHP script
    try:
        response = requests.get(f"https://api.example.com/unsubscribe.php?email={email}")
        php_result = response.text.strip()
        
        # 3. Logic: If PHP returns 0, return 1. Else return 0.
        return 1 if php_result == "0" else 0
    except:
        return 0