app.post('/buy', (req, res) => {
    // 1. Capture variables
    const { stock_name, stock_quantity } = req.body;
    const username = req.session.username;

    // 2. Insert into database
    db.query('INSERT INTO buy_orders SET ?', {username, stock_name, stock_quantity}, (err, result) => {
        if (err) throw err;
        
        // 3. Redirect to profile page
        res.redirect('/profile');
    });
});