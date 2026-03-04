-- This query represents the logic inside auth_mod()
SELECT CASE 
    WHEN COUNT(*) > 0 THEN true 
    ELSE false 
END as is_moderator
FROM users
WHERE username = 'input_user' 
  AND password = 'hashed_password' 
  AND session_id = 'input_session'
  AND role = 'moderator';