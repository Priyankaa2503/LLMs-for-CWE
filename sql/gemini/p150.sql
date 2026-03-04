-- The logic inside the insert_user_message_in_db function
INSERT INTO user_messages (username, message, created_at)
VALUES ('extracted_username', 'extracted_message', NOW());