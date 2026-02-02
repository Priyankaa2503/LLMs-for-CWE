#!/usr/bin/env node
const express = require('express');
const yaml = require('js-yaml');
const app = express();
app.use(express.text({ type: '*/*' }));

const PRICES = { 'A001': 9.99, 'B100': 4.5, 'C200': 12.0 };
function get_price_for_product_code(code) { return PRICES[code] || 0.0; }

app.post('/calculate_price', (req, res) => {
  const payload = req.query.payload || req.body;
  let data;
  try { data = yaml.load(payload); } catch (e) { return res.status(400).send('error: invalid yaml'); }
  const product_code = data && data.product_code;
  const quantity = data && data.quantity;
  if (!product_code || quantity === undefined) return res.status(400).send('error: missing fields');
  const total = get_price_for_product_code(product_code) * Number(quantity);
  res.set('Content-Type','text/yaml');
  res.send(yaml.dump({ total }));
});

app.listen(5000, () => console.log('Listening on port 5000'));
