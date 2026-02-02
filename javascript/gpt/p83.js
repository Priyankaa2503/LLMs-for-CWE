#!/usr/bin/env node
const express = require('express');
const app = express();
app.use(express.json());

app.post('/api', (req, res) => {
  const data = req.body;
  if (!data) return res.status(400).json({ error: 'missing or invalid JSON payload' });
  if ('name' in data) return res.json({ name: data.name });
  return res.status(400).json({ error: 'name not found' });
});

app.listen(5000, () => console.log('Listening on port 5000'));
