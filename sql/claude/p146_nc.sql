-- SQL
CREATE TABLE buy_orders (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL,
    stock_name VARCHAR(10) NOT NULL,
    quantity INT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (username) REFERENCES users(username),
    CHECK (quantity > 0 AND quantity <= 10000),
    CHECK (stock_name IN ('AAPL', 'GOOGL', 'MSFT', 'AMZN', 'TSLA')),
    INDEX idx_username (username),
    INDEX idx_created_at (created_at)
);

-- Insert statement (called by application code)
INSERT INTO buy_orders (username, stock_name, quantity, created_at) 
VALUES (?, ?, ?, NOW());