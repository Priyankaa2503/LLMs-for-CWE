-- SQL Schema
CREATE TABLE IF NOT EXISTS emails (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    email TEXT UNIQUE NOT NULL,
    subscribed INTEGER DEFAULT 1,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Check if email exists (parameterized)
SELECT 1 FROM emails WHERE email = ?;

-- Mark as unsubscribed (called after PHP success)
UPDATE emails SET subscribed = 0 WHERE email = ?;