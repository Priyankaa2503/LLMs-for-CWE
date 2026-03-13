-- SQL Query for checking if a username exists
-- This query should be executed using parameterized/prepared statements from application code
-- The placeholder (?) represents the parameterized username input

-- Basic query with normalization
SELECT 1 FROM users WHERE LOWER(username) = ? LIMIT 1;

-- Alternative: Using EXISTS for efficiency
SELECT EXISTS(SELECT 1 FROM users WHERE LOWER(username) = ?) AS user_exists;

-- Alternative: Using COUNT (returns count instead of boolean)
SELECT COUNT(*) AS user_count FROM users WHERE LOWER(username) = ?;

-- Table structure example (for reference)
CREATE TABLE users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(255) NOT NULL UNIQUE,
    email VARCHAR(255) NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Create index on username for performance
CREATE INDEX idx_username ON users(username);

/*
SECURITY IMPLEMENTATION NOTES:

1. PARAMETERIZED QUERIES:
   - Always use the ? placeholder syntax with parameterized statements
   - Never concatenate user input directly into SQL strings
   - Example (wrong): "SELECT 1 FROM users WHERE username = '" + username + "'"
   - Example (correct): "SELECT 1 FROM users WHERE LOWER(username) = ?" with [username]

2. USERNAME NORMALIZATION:
   - Use LOWER() function in SQL to handle case-insensitive lookups
   - In application code, normalize input: trim(), toLowerCase()
   - This prevents bypassing checks with case variations

3. ERROR HANDLING:
   - Don't expose database error messages to users
   - Log technical errors securely on server side
   - Return only generic failure/success to client
   - Never include SQL query details in error responses

4. QUERY OPTIMIZATION:
   - Use LIMIT 1 to stop searching after first match
   - Add indexes on username column for performance
   - Use EXISTS or COUNT based on your application's return type need

5. ADDITIONAL SECURITY:
   - Implement rate limiting on authentication attempts
   - Log failed login attempts for security monitoring
   - Use prepared statements in all application code
   - Validate username format before database query
   - Consider adding a delay on failed attempts (timing attack mitigation)
*/