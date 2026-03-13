-- SQL (Parameterized Query Pattern)
-- DELETE operation with parameterized query
PREPARE unsubscribe_stmt FROM 
    'DELETE FROM subscribers WHERE email = ?';

-- Usage (language-specific):
-- Python: cursor.execute('DELETE FROM subscribers WHERE email = ?', (email,))
-- JavaScript: db.run('DELETE FROM subscribers WHERE email = ?', [email])
-- Java: PreparedStatement stmt = conn.prepareStatement('DELETE FROM subscribers WHERE email = ?');
--       stmt.setString(1, email);
--       stmt.executeUpdate();

-- Schema
CREATE TABLE subscribers (
    id INT AUTO_INCREMENT PRIMARY KEY,
    email VARCHAR(254) NOT NULL UNIQUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_email ON subscribers(email);