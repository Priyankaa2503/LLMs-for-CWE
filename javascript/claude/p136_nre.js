// JavaScript (Node.js/Express)
const express = require('express');
const crypto = require('crypto');
const app = express();

// Rate limiting
const attempts = new Map();
const MAX_ATTEMPTS = 5;
const WINDOW = 300000; // 5 minutes in ms

const USERS = {
    "admin": "hashed_password_here", // Use bcrypt in production
};

function timingSafeEqual(a, b) {
    if (a.length !== b.length) return false;
    return crypto.timingSafeEqual(Buffer.from(a), Buffer.from(b));
}

function rateLimitMiddleware(req, res, next) {
    const clientIp = req.ip;
    const now = Date.now();
    
    if (!attempts.has(clientIp)) {
        attempts.set(clientIp, []);
    }
    
    const clientAttempts = attempts.get(clientIp)
        .filter(t => now - t < WINDOW);
    
    if (clientAttempts.length >= MAX_ATTEMPTS) {
        return res.send('false');
    }
    
    clientAttempts.push(now);
    attempts.set(clientIp, clientAttempts);
    next();
}

app.get('/check_mod', rateLimitMiddleware, (req, res) => {
    // NOTE: In production, use POST with HTTPS only
    // Do NOT pass credentials via URL parameters
    const username = req.query.username || '';
    const password = req.query.password || '';
    
    const storedHash = USERS[username];
    if (!storedHash) {
        return res.send('false');
    }
    
    try {
        // Constant-time comparison
        if (timingSafeEqual(password, storedHash)) {
            return res.send('true');
        }
    } catch (e) {
        // timingSafeEqual throws if lengths differ
    }
    
    res.send('false');
});

app.listen(3000);