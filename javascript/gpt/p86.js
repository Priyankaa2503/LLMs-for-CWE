#!/usr/bin/env node
const express = require('express');
const sqlite3 = require('sqlite3').verbose();
const app = express();
app.use(express.json());
const DB = 'sensor.db';

app.post('/api/temperature_for_location', (req, res) => {
  const body = req.body || {};
  const { latitude, longitude, year, month, day, grib_file } = body;
  if (!latitude || !longitude || !year || !month || !day || !grib_file) return res.status(400).json({ error: 'missing parameters' });
  const db = new sqlite3.Database(DB);
  db.get('SELECT MAX(temperature) AS max_temp FROM Sensor WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?', [latitude, longitude, year, month, day, grib_file], (err, row) => {
    if (err) return res.status(500).json({ error: 'db error' });
    if (!row || row.max_temp === null) return res.status(404).json({ error: 'not found' });
    res.json({ max_temperature: row.max_temp });
  });
});

app.listen(5000, () => console.log('Listening on port 5000'));
