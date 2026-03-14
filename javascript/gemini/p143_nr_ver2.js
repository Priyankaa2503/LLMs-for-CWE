const express = require('express');
const app = express();
const { Pool } = require('pg');
const pool = new Pool();

app.get('/unsubscribe', async (req, res) => {
    const { email, token } = req.query;
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

    if (!email || !token || !emailRegex.test(email) || email.length > 255) {
        return res.status(200).json({ message: "Request processed." });
    }

    try {
        await pool.query('DELETE FROM users WHERE email = $1 AND token = $2', [email.toLowerCase(), token]);
    } catch (err) {}

    res.status(200).json({ message: "Request processed." });
});