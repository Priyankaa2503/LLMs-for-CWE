#!/usr/bin/env node
const express = require('express');
const app = express();

const PRICES = { 'A001': 9.99, 'B100': 4.5, 'C200': 12.0 };

function get_price_for_product_code(code) { return PRICES[code] || 0.0; }

app.get('/price', (req, res) => {
  const product_code = req.query.product_code;
  const quantity = parseFloat(req.query.quantity);
  if (!product_code || Number.isNaN(quantity)) return res.status(400).json({ error: 'missing parameters' });
  const price = get_price_for_product_code(product_code);
  res.json({ total: price * quantity });
});

app.listen(5000, () => console.log('App running on port 5000'));
