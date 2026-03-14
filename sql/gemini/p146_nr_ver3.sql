CREATE TABLE orders (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50) NOT NULL,
    stock_name VARCHAR(10) NOT NULL,
    quantity INT NOT NULL CHECK (quantity > 0 AND quantity <= 10000),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Parameterized Insert Template
-- INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?);