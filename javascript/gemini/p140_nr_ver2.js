const { Pool } = require('pg');
const pool = new Pool({ /* Restricted Read-Only Credentials */ });

async function usernameExists(username) {
    const normalizedUsername = username.trim().toLowerCase();
    
    try {
        const query = 'SELECT 1 FROM users WHERE username = $1';
        const result = await pool.query(query, [normalizedUsername]);
        return result.rowCount > 0;
    } catch (err) {
        return false;
    }
}