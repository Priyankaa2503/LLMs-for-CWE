// JavaScript (Node.js + Express)
const express = require('express');
const crypto = require('crypto');
const app = express();

// Simple in-memory rate limiting (use Redis in production)
const requestLog = new Map();
const MAX_ATTEMPTS = 5;
const TIME_WINDOW = 60000; // milliseconds

const CORRECT_USERNAME = "admin";
const CORRECT_PASSWORD = "secret123";

function constantTimeEqual(a, b) {
    return crypto.timingSafeEqual(Buffer.from(a), Buffer.from(b));
}

function rateLimitMiddleware(req, res, next) {
    const clientIp = req.ip;
    const now = Date.now();
    
    if (!requestLog.has(clientIp)) {
        requestLog.set(clientIp, []);
    }
    
    const times = requestLog.get(clientIp)
        .filter(t => now - t < TIME_WINDOW);
    
    if (times.length >= MAX_ATTEMPTS) {
        return res.status(429).send('false');
    }
    
    times.push(now);
    requestLog.set(clientIp, times);
    next();
}

app.get('/check_mod', rateLimitMiddleware, (req, res) => {
    // SECURITY: In production, use POST+HTTPS instead of GET with credentials in URL
    const username = req.query.username || '';
    const password = req.query.password || '';
    
    try {
        // Constant-time comparison to prevent timing attacks
        const usernameMatch = constantTimeEqual(username, CORRECT_USERNAME);
        const passwordMatch = constantTimeEqual(password, CORRECT_PASSWORD);
        
        // Don't leak which field was wrong
        if (usernameMatch && passwordMatch) {
            return res.send('true');
        }
        return res.send('false');
    } catch (err) {
        // Handle timing-safe comparison errors gracefully
        return res.send('false');
    }
});

app.listen(3000, () => console.log('Server running on port 3000'));