const express = require('express');
const rateLimit = require('express-rate-limit');
const crypto = require('crypto');

const app = express();

// ⚠️ WARNING: Query parameters containing credentials are transmitted in plaintext in URLs.
// This endpoint MUST only be used over HTTPS. Credentials should be sent via POST body or secure headers in production.

const STORED_USERNAME = "admin";
const STORED_PASSWORD = "secure_password_hash_or_key";

// Rate limiting middleware: 5 requests per minute per IP
const limiter = rateLimit({
    windowMs: 60 * 1000, // 1 minute
    max: 5, // Limit each IP to 5 requests per windowMs
    message: 'false',
    standardHeaders: false,
    legacyHeaders: false,
});

// Constant-time string comparison to prevent timing attacks
function timingSafeEqual(a, b) {
    const bufA = Buffer.from(a, 'utf8');
    const bufB = Buffer.from(b, 'utf8');
    
    if (bufA.length !== bufB.length) {
        return false;
    }
    
    return crypto.timingSafeEqual(bufA, bufB);
}

app.get('/check_mod', limiter, (req, res) => {
    const username = req.query.username || '';
    const password = req.query.password || '';
    
    try {
        // Constant-time comparison prevents timing attacks
        const usernameMatch = timingSafeEqual(username, STORED_USERNAME);
        const passwordMatch = timingSafeEqual(password, STORED_PASSWORD);
        
        // Both must match; no partial success disclosure
        if (usernameMatch && passwordMatch) {
            return res.status(200).send('true');
        }
        
        // Generic failure response - no detail about which credential failed
        return res.status(200).send('false');
    } catch (err) {
        // If comparison fails (length mismatch, etc.), return generic failure
        return res.status(200).send('false');
    }
});

app.listen(3000, () => {
    console.log('Server running on https://localhost:3000 (HTTPS required in production)');
});