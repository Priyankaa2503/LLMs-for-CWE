// Node.js (Express)
const express = require('express');
const jwt = require('jsonwebtoken');
const sqlite3 = require('sqlite3').verbose();
const app = express();

const SECRET_KEY = 'your-secret-key';
const db = new sqlite3.Database('users.db');

function validateEmail(email) {
    if (!email || email.length > 254) return null;
    const pattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    return pattern.test(email) ? email.toLowerCase().trim() : null;
}

app.get('/unsubscribe', (req, res) => {
    const token = req.query.token;
    
    if (!token) {
        return res.status(200).json({ 
            message: 'If this email was subscribed, it has been unsubscribed.' 
        });
    }
    
    try {
        const decoded = jwt.verify(token, SECRET_KEY);
        const email = decoded.email;
        
        const validatedEmail = validateEmail(email);
        if (!validatedEmail) {
            return res.status(200).json({ 
                message: 'If this email was subscribed, it has been unsubscribed.' 
            });
        }
        
        db.run('DELETE FROM subscribers WHERE email = ?', [validatedEmail], (err) => {
            return res.status(200).json({ 
                message: 'If this email was subscribed, it has been unsubscribed.' 
            });
        });
    } catch (err) {
        return res.status(200).json({ 
            message: 'If this email was subscribed, it has been unsubscribed.' 
        });
    }
});

app.listen(3000);