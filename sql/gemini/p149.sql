-- Creating the table
CREATE TABLE user_messages (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50),
    message TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- The insertion query
INSERT INTO user_messages (username, message) 
VALUES ('JohnDoe', 'Hello world!');

-- The retrieval query (for displaying)
SELECT username, message, created_at 
FROM user_messages 
ORDER BY created_at DESC;