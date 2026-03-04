const express = require('express');
const app = express();
app.use(express.urlencoded({ extended: true }));

app.post('/buy_order', (req, res) => {
    const { stock_name, quantity } = req.body;
    
    // Database logic (Pseudo-code for brevity)
    db.query('INSERT INTO stock_orders SET ?', {stock_name, quantity}, (err, result) => {
        if (err) throw err;
        // Redirect to view page
        res.redirect('/stock_view');
    });
});