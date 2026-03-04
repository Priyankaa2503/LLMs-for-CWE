-- The schema setup
CREATE TABLE trades (
    id INT PRIMARY KEY AUTO_INCREMENT,
    stock_name VARCHAR(10),
    quantity INT,
    purchase_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- The insertion logic
INSERT INTO trades (stock_name, quantity) 
VALUES ('AAPL', 10);