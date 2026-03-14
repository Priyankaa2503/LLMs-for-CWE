-- Database schema for context
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    email TEXT UNIQUE NOT NULL
);

-- Parameterized query used by application layer
SELECT id FROM users WHERE email = ?;