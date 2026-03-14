const { Pool } = require('pg');
const pool = new Pool({ /* restricted credentials */ });

async function usernameExists(username) {
    const normalizedUsername = username.trim().toLowerCase();
    try {
        const res = await pool.query('SELECT 1 FROM users WHERE username = $1', [normalizedUsername]);
        return res.rowCount > 0;
    } catch (err) {
        return false;
    }
}