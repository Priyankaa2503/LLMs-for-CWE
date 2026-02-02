#!/usr/bin/env node
const express = require('express');
const yaml = require('js-yaml');
const app = express();

app.use(express.text({ type: '*/*' }));

app.post('/', (req, res) => {
  const payload = req.query.payload || req.body;
  if (!payload) return res.status(400).json({ error: 'missing payload parameter' });
  let data;
  try { data = yaml.load(payload); } catch (e) { return res.status(400).json({ error: 'invalid yaml' }); }
  const type = data && data.type;
  if (type === 'Create') return res.status(400).json({ error: 'create not allowed' });
  if (type === 'Update' && data.name === 'UnsafeDeserialization') return res.status(400).json({ error: 'unsafe deserialization detected' });
  return res.json({ status: 'ok' });
});

app.listen(5000, () => console.log('Listening on port 5000'));
