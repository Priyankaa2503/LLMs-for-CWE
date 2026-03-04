-- This query returns 1 if the email exists, 0 if it doesn't.
SELECT EXISTS(
    SELECT 1 FROM users 
    WHERE email = 'user@example.com'
) AS email_exists;