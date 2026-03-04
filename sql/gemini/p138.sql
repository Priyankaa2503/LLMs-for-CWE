-- Creating the table structure
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50),
    is_moderator BOOLEAN DEFAULT FALSE
);

-- The specific query used by the app logic
SELECT is_moderator 
FROM users 
WHERE id = 123;