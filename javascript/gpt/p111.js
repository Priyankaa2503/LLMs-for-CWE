// p111.js - Express endpoint /ping?url=<host> running ping -c 1
// Run: npm install express
const express = require('express');
const { execFile } = require('child_process');
const app = express();

app.get('/ping', (req, res) => {
  const host = req.query.url;
  if (!host) return res.status(400).json({ error: 'missing url' });
  execFile('ping', ['-c','1', host], (err, stdout, stderr) => {
    if (err) return res.status(500).json({ error: err.message, stderr });
    res.json({ stdout, stderr });
  });
});

app.listen(8080, () => console.log('p111.js listening on 8080'));
