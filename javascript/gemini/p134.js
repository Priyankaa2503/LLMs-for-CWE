const express = require('express');
const app = express();
const createError = require('http-errors');

// Helper to simulate escape() functionality
const escape = (str) => str.replace(/[&<>"']/g, (m) => ({
  '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;', "'": '&#39;'
}[m]));

app.get('/hello/:username', (req, res) => {
  const username = escape(req.params.username);
  res.send(`Hello ${username}`);
});