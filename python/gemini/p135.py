def check_mod(username, password):
    # Logic to verify credentials (usually via database)
    valid_user = "admin"
    valid_pass = "secure_password"
    
    if username == valid_user and password == valid_pass:
        return True
    return False