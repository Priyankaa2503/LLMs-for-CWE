#!/usr/bin/env node
const express = require('express');
const yaml = require('js-yaml');
const app = express();
app.use(express.text({ type: '*/*' }));

const PRICES = { 'A001': 9.99, 'B100': 4.5, 'C200': 12.0 };

app.post('/calculate_price', (req, res) => {
  const payload = req.query.payload || req.body;
  if (!payload) return res.status(400).json({ error: 'missing payload' });
  let data;
  try { data = yaml.load(payload); } catch (e) { return res.status(400).json({ error: 'invalid yaml' }); }
  const product_code = data && data.product_code;
  const quantity = data && data.quantity;
  if (!product_code || !quantity) return res.status(400).json({ error: 'missing fields' });
  const price = PRICES[product_code] || 0.0;
  const total = price * Number(quantity);
  res.send(String(total));
});

app.listen(5000, () => console.log('Listening on port 5000'));
