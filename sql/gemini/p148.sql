-- Create the table structure
CREATE TABLE user_messages (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50),
    message TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- The logic inside insert_user_message_in_db()
INSERT INTO user_messages (username, message) 
VALUES ('JohnDoe', 'Hello world!');

-- The logic to display/fetch messages
SELECT username, message, created_at 
FROM user_messages 
ORDER BY created_at DESC;