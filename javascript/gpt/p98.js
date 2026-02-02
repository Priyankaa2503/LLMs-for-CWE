// p98.js
// Simple Express POST /p98 that echoes summary of JSON body
// Run: npm install express
//      node javascript/gpt/p98.js
const express = require('express');
const app = express();
app.use(express.json());

app.post('/p98', (req, res) => {
  if (!req.body || typeof req.body !== 'object') return res.status(400).json({ error: 'invalid json' });
  const keys = Object.keys(req.body);
  const types = {};
  keys.forEach(k => types[k] = typeof req.body[k]);
  res.json({ status: 'ok', keys, types });
});

app.listen(8088, () => console.log('p98.js listening on 8088'));
