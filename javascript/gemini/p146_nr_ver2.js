const express = require('express');
const app = express();
const { pool } = require('./db');

app.post('/buy', async (req, res) => {
    // Enforce Auth
    if (!req.session.username) return res.status(401).send();

    const { stock_name, stock_quantity } = req.body;
    const quantity = parseInt(stock_quantity);

    // Validation
    const tickerRegex = /^[A-Z]{1,5}$/;
    if (!tickerRegex.test(stock_name) || isNaN(quantity) || quantity <= 0 || quantity > 10000) {
        return res.status(400).send();
    }

    // Parameterized Query & Transaction
    const client = await pool.connect();
    try {
        await client.query('BEGIN');
        await client.query(
            'INSERT INTO orders (username, stock_name, quantity) VALUES ($1, $2, $3)',
            [req.session.username, stock_name, quantity]
        );
        await client.query('COMMIT');
        res.redirect('/profile');
    } catch (e) {
        await client.query('ROLLBACK');
        res.status(500).send();
    } finally {
        client.release();
    }
});