// JavaScript (Node.js with Express)
const express = require('express');
const crypto = require('crypto');
const sqlite3 = require('sqlite3').verbose();
const { validate: validateEmail } = require('email-validator');

const app = express();
const SECRET_KEY = 'your-secret-key-here';
const db = new sqlite3.Database('users.db');

function validateAndNormalizeEmail(email) {
  const trimmed = email.trim();
  if (!validateEmail(trimmed)) {
    return null;
  }
  return trimmed.toLowerCase();
}

function generateUnsubscribeToken(email) {
  return crypto
    .createHmac('sha256', SECRET_KEY)
    .update(email.toLowerCase())
    .digest('hex');
}

function verifyUnsubscribeToken(email, token) {
  const expectedToken = generateUnsubscribeToken(email);
  try {
    return crypto.timingSafeEqual(
      Buffer.from(token),
      Buffer.from(expectedToken)
    );
  } catch {
    return false;
  }
}

app.get('/api/unsubscribe', (req, res) => {
  const email = (req.query.email || '').trim();
  const token = (req.query.token || '').trim();

  const normalizedEmail = validateAndNormalizeEmail(email);
  if (!normalizedEmail) {
    return res.status(200).json({ message: 'Unsubscribe request processed.' });
  }

  if (!token || !verifyUnsubscribeToken(normalizedEmail, token)) {
    return res.status(200).json({ message: 'Unsubscribe request processed.' });
  }

  db.get('SELECT id FROM users WHERE email = ?', [normalizedEmail], (err, row) => {
    if (err) {
      console.error('Database error:', err);
      return res.status(200).json({ message: 'Unsubscribe request processed.' });
    }

    if (row) {
      const timestamp = new Date().toISOString();
      db.run('DELETE FROM users WHERE email = ?', [normalizedEmail]);
      db.run(
        'INSERT INTO unsubscribe_log (email, timestamp) VALUES (?, ?)',
        [normalizedEmail, timestamp]
      );
    }

    res.status(200).json({ message: 'Unsubscribe request processed.' });
  });
});

app.listen(3000);