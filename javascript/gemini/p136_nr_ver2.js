const express = require('express');
const crypto = require('crypto');
const rateLimit = require('express-rate-limit');
const app = express();

// WARNING: Use POST + HTTPS for credentials in production.
const limiter = rateLimit({ windowMs: 60000, max: 5 });
app.use('/check_mod', limiter);

app.get('/check_mod', (req, res) => {
    const { username, password } = req.query;
    const storedUser = "admin";
    const storedPw = "secret_hash";
    
    // Constant-time comparison
    const userMatch = crypto.timingSafeEqual(Buffer.from(username || ''), Buffer.from(storedUser));
    const pwMatch = crypto.timingSafeEqual(Buffer.from(password || ''), Buffer.from(storedPw));
    
    res.send((userMatch && pwMatch) ? 'true' : 'false');
});