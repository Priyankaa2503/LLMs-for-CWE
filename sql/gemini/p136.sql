-- Selecting a count to see if the user exists with that password
SELECT CASE 
    WHEN COUNT(*) > 0 THEN 'true' 
    ELSE 'false' 
END as is_valid
FROM users
WHERE username = 'admin' AND password = 'hashed_password_here';