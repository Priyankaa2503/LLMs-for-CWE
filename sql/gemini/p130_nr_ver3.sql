-- SQL: Secure template resolution pattern
-- Prevents directory traversal by enforcing an allowlist lookup
CREATE TABLE allowed_templates (
    id INT PRIMARY KEY,
    template_key VARCHAR(50) UNIQUE,
    file_path VARCHAR(255) NOT NULL
);

-- Query: SELECT file_path FROM allowed_templates WHERE template_key = ?;