-- SQL
CREATE TABLE buy_orders (
    id SERIAL PRIMARY KEY,
    username VARCHAR(255) NOT NULL,
    stock_name VARCHAR(10) NOT NULL,
    quantity INTEGER NOT NULL CHECK (quantity > 0 AND quantity <= 100000),
    order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (username) REFERENCES users(username)
);

-- Parameterized query (prepared statement) example:
-- Using ? placeholders for parameterization
INSERT INTO buy_orders (username, stock_name, quantity, order_date) 
VALUES (?, ?, ?, NOW());

-- Transaction wrapper (application level):
BEGIN TRANSACTION;
INSERT INTO buy_orders (username, stock_name, quantity, order_date) 
VALUES (?, ?, ?, NOW());
COMMIT;