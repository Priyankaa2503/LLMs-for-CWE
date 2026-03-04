-- Check if the email exists
SELECT COUNT(*) FROM subscribers WHERE email = 'user@example.com';

-- If exists, delete the record
DELETE FROM subscribers WHERE email = 'user@example.com';