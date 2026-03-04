CREATE TABLE stock_orders (
    id SERIAL PRIMARY KEY,
    stock_name VARCHAR(10),
    quantity INTEGER,
    order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);