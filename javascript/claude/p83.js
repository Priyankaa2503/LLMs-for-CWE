// p83.js - Express POST /api endpoint
const express = require('express');
const app = express();
app.use(express.json());

app.post('/api', (req, res) => {
  if (!req.body) return res.status(400).json({ error: 'invalid json' });
  const name = req.body.name;
  if (!name) return res.status(400).json({ error: 'missing name' });
  res.json({ name });
});

app.listen(5000, () => console.log('p83.js listening on 5000'));
