// JavaScript Node.js Express - Secure Unsubscribe Endpoint
const express = require('express');
const crypto = require('crypto');
const sqlite3 = require('sqlite3').verbose();
const app = express();

const SECRET_KEY = process.env.SECRET_KEY || 'dev-secret-change-in-prod';
const TOKEN_MAX_AGE_MS = 86400000; // 24 hours
const DB_PATH = 'subscriptions.db';
const EMAIL_REGEX = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

const db = new sqlite3.Database(DB_PATH, (err) => {
    if (err) console.error('DB error:', err);
});

// Initialize database
db.serialize(() => {
    db.run(`CREATE TABLE IF NOT EXISTS subscriptions (
        id INTEGER PRIMARY KEY,
        email TEXT UNIQUE,
        subscribed INTEGER,
        created_at DATETIME
    )`);
});

/**
 * Generate HMAC-signed, time-limited unsubscribe token
 * Token format: base64(timestamp:email).signature
 */
function generateUnsubscribeToken(email) {
    const timestamp = Date.now();
    const payload = Buffer.from(`${timestamp}:${email}`).toString('base64');
    const signature = crypto
        .createHmac('sha256', SECRET_KEY)
        .update(payload)
        .digest('base64')
        .replace(/\+/g, '-')
        .replace(/\//g, '_')
        .replace(/=/g, '');
    
    return `${payload}.${signature}`;
}

/**
 * Verify token signature and expiration
 */
function verifyUnsubscribeToken(token) {
    try {
        const [payload, signature] = token.split('.');
        if (!payload || !signature) return null;
        
        // Verify signature (constant-time comparison)
        const computedSignature = crypto
            .createHmac('sha256', SECRET_KEY)
            .update(payload)
            .digest('base64')
            .replace(/\+/g, '-')
            .replace(/\//g, '_')
            .replace(/=/g, '');
        
        if (!crypto.timingSafeEqual(
            Buffer.from(signature),
            Buffer.from(computedSignature)
        )) {
            return null;
        }
        
        // Decode and verify expiration
        const [timestamp, email] = Buffer.from(payload, 'base64').toString().split(':');
        const tokenAge = Date.now() - parseInt(timestamp);
        
        if (tokenAge > TOKEN_MAX_AGE_MS) {
            return null;
        }
        
        return email;
    } catch (err) {
        return null;
    }
}

/**
 * Normalize email for security
 */
function normalizeEmail(email) {
    if (typeof email !== 'string') return null;
    
    email = email.trim().toLowerCase();
    
    if (!EMAIL_REGEX.test(email) || email.length > 254) {
        return null;
    }
    
    return email;
}

/**
 * Secure unsubscribe endpoint using signed tokens.
 * GET /unsubscribe?token=<signed_token>
 */
app.get('/unsubscribe', (req, res) => {
    const token = (req.query.token || '').trim();
    
    // Empty token - generic response
    if (!token) {
        return res.json({ status: 'ok' });
    }
    
    // Verify token signature and expiration
    let email = verifyUnsubscribeToken(token);
    if (!email) {
        // Invalid/expired token - generic response
        return res.json({ status: 'ok' });
    }
    
    // Normalize and validate email
    email = normalizeEmail(email);
    if (!email) {
        return res.json({ status: 'ok' });
    }
    
    // Parameterized query - prevents SQL injection
    db.get(
        'SELECT id FROM subscriptions WHERE email = ? AND subscribed = 1',
        [email],
        (err, row) => {
            if (err) {
                // Log but don't expose error
                console.error('DB error:', err);
                return res.json({ status: 'ok' });
            }
            
            if (row) {
                // Unsubscribe using parameterized query
                db.run(
                    'UPDATE subscriptions SET subscribed = 0 WHERE email = ?',
                    [email],
                    (err) => {
                        if (err) {
                            console.error('Update error:', err);
                        }
                        // Trigger external mailing list unsubscribe
                        // await mailingListService.unsubscribe(email);  // Pseudo-code
                    }
                );
            }
            
            // Always return same response - prevents enumeration
            res.json({ status: 'ok' });
        }
    );
});

app.listen(3000, () => {
    console.log('Server running on port 3000');
});

module.exports = { generateUnsubscribeToken, verifyUnsubscribeToken };