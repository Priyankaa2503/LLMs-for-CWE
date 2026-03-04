-- We assume a 'users' table with a 'role' or 'is_moderator' column
SELECT EXISTS (
    SELECT 1 
    FROM users 
    WHERE user_id = ? AND role = 'moderator'
);