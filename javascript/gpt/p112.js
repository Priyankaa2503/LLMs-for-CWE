// p112.js - Express endpoint /ping2?url=<host> (similar to p111)
const express = require('express');
const { execFile } = require('child_process');
const app = express();

app.get('/ping2', (req, res) => {
  const host = req.query.url;
  if (!host) return res.status(400).json({ error: 'missing url' });
  execFile('ping', ['-c','1', host], (err, stdout, stderr) => {
    if (err) return res.status(500).json({ error: err.message, stderr });
    res.json({ stdout });
  });
});

app.listen(8081, () => console.log('p112.js listening on 8081'));
