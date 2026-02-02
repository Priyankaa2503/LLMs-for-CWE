#!/usr/bin/env node
const express = require('express');
const sqlite3 = require('sqlite3').verbose();
const app = express();
app.use(express.json());
const DB='sensor.db';

app.post('/api/temperature_for_location', (req, res) => {
  const { latitude, longitude, date } = req.body || {};
  if (!latitude || !longitude || !date) return res.status(400).json({ error: 'missing parameters' });
  const db = new sqlite3.Database(DB);
  db.get('SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=? LIMIT 1', [latitude, longitude, date], (err, row) => {
    if (err) return res.status(500).json({ error: 'db error' });
    if (!row) return res.status(404).json({ error: 'not found' });
    res.json({ temperature: row.temperature });
  });
});

app.listen(5000, ()=>console.log('Listening on port 5000'));
