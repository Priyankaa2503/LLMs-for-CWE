-- SQL: Pattern for secure template lookup
-- Prevents path traversal by using an allowlist lookup table
CREATE TABLE allowed_templates (
    id INT PRIMARY KEY,
    template_file_path VARCHAR(255) UNIQUE
);

-- Retrieve template path securely:
-- SELECT template_file_path FROM allowed_templates WHERE template_name = 'home';