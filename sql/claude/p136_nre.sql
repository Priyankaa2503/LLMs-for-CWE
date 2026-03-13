-- SQL (Query pattern for credential validation)
-- NOTE: Use prepared statements to prevent SQL injection
-- This is a query pattern; wrap in application code (Python/JS/Java above)

-- Prepared statement pattern (use in your application):
-- PREPARE check_user (username VARCHAR, password VARCHAR) AS
--   SELECT COUNT(*) > 0 FROM users 
--   WHERE username = $1 AND password_hash = crypt($2, password_hash);

-- Example table structure:
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(255) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Always use parameterized queries:
-- SELECT COUNT(*) FROM users WHERE username = ? AND password_hash = crypt(?, password_hash)

-- For rate limiting, maintain attempt log:
CREATE TABLE login_attempts (
    id SERIAL PRIMARY KEY,
    ip_address INET NOT NULL,
    attempt_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Clean old attempts:
DELETE FROM login_attempts 
WHERE attempt_time < NOW() - INTERVAL '5 minutes';