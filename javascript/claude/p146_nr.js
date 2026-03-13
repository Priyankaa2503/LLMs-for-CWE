// JavaScript (Node.js + Express + PostgreSQL)
const express = require('express');
const session = require('express-session');
const { Pool } = require('pg');

const app = express();
const pool = new Pool({
  connectionString: 'postgresql://user:pass@localhost/stocks'
});

const VALID_STOCKS = new Set(['AAPL', 'GOOGL', 'MSFT', 'AMZN', 'TSLA']);
const MAX_QUANTITY = 100000;

app.use(session({
  secret: 'secret_key',
  resave: false,
  saveUninitialized: false,
  cookie: { httpOnly: true, secure: true }
}));

app.use(express.urlencoded({ extended: false }));

const authRequired = (req, res, next) => {
  if (!req.session.username) {
    return res.redirect('/login');
  }
  next();
};

app.post('/buy', authRequired, async (req, res) => {
  const username = req.session.username;
  const stock_name = (req.body.stock_name || '').toUpperCase();
  const stock_quantity = parseInt(req.body.stock_quantity, 10);

  if (!VALID_STOCKS.has(stock_name)) {
    return res.status(400).send('Invalid stock');
  }

  if (!Number.isInteger(stock_quantity) || stock_quantity <= 0 || stock_quantity > MAX_QUANTITY) {
    return res.status(400).send('Invalid quantity');
  }

  const client = await pool.connect();
  try {
    await client.query('BEGIN');
    await client.query(
      'INSERT INTO buy_orders (username, stock_name, quantity, created_at) VALUES ($1, $2, $3, NOW())',
      [username, stock_name, stock_quantity]
    );
    await client.query('COMMIT');
    res.redirect('/profile');
  } catch (err) {
    await client.query('ROLLBACK');
    res.status(500).send('Database error');
  } finally {
    client.release();
  }
});