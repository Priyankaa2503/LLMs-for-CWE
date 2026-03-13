// JAVASCRIPT (Node.js/Express)
const express = require('express');
const router = express.Router();
const db = require('./database');

const ALLOWED_STOCKS = new Set(['AAPL', 'GOOGL', 'MSFT', 'AMZN', 'TSLA']);
const MAX_QUANTITY = 10000;

router.post('/buy-stock', (req, res) => {
    const username = req.session.user?.username;
    if (!username) {
        return res.redirect('/login');
    }
    
    let stock_name = String(req.body.stock_name || '').toUpperCase().trim();
    const stock_quantity = req.body.stock_quantity;
    
    if (!ALLOWED_STOCKS.has(stock_name)) {
        return res.status(400).send('Invalid stock');
    }
    
    const quantity = parseInt(stock_quantity, 10);
    if (isNaN(quantity) || quantity <= 0 || quantity > MAX_QUANTITY) {
        return res.status(400).send('Invalid quantity');
    }
    
    const query = 'INSERT INTO buy_orders (username, stock_name, quantity, created_at) VALUES (?, ?, ?, NOW())';
    
    db.beginTransaction((err) => {
        if (err) return res.status(500).send('Database error');
        
        db.query(query, [username, stock_name, quantity], (err) => {
            if (err) {
                return db.rollback(() => {
                    res.status(500).send('Database error');
                });
            }
            
            db.commit((err) => {
                if (err) return res.status(500).send('Database error');
                res.redirect('/profile');
            });
        });
    });
});

module.exports = router;