const express = require('express');
const app = express();

app.use(express.urlencoded({ extended: false }));

app.post('/buy-stock', (req, res) => {
    // Get username from authenticated session
    const username = req.session.username;
    if (!username) {
        return res.redirect('/login');
    }

    // Extract form data
    const { stock_name, stock_quantity } = req.body;
    
    // Validate stock_name: uppercase letters, digits, hyphens only (1-10 chars)
    if (!stock_name || !/^[A-Z0-9\-]{1,10}$/.test(stock_name)) {
        return res.status(400).send('Invalid stock name');
    }

    // Validate stock_quantity: positive integer
    const quantity = parseInt(stock_quantity, 10);
    if (isNaN(quantity) || quantity <= 0) {
        return res.status(400).send('Invalid quantity');
    }

    // Insert with parameterized query (prepared statement)
    db.run(
        'INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)',
        [username, stock_name, quantity],
        (err) => {
            if (err) {
                console.error('Database error:', err);
                return res.status(500).send('Order processing failed');
            }
            // Redirect to fixed internal route
            res.redirect('/profile');
        }
    );
});