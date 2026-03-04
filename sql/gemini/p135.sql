-- This query looks for a record matching the input
SELECT id, username 
FROM users 
WHERE username = 'input_user' 
AND password_hash = 'hashed_input_password';