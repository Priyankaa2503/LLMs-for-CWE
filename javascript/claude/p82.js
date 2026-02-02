// p82.js - Express /api endpoint with JSON payload
// Run: npm install express
const express = require('express');
const app = express();
app.use(express.json());

app.get('/api', (req, res) => {
  const payload = req.query.payload;
  if (!payload) return res.status(400).json({ error: 'missing payload' });
  try {
    const data = JSON.parse(payload);
    return res.json({ name: data.name });
  } catch (e) {
    return res.status(400).json({ error: e.message });
  }
});

app.post('/api', (req, res) => {
  if (!req.body) return res.status(400).json({ error: 'missing payload' });
  return res.json({ name: req.body.name });
});

app.listen(5000, () => console.log('p82.js listening on 5000'));
