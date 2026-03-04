const { Pool } = require('pg');

async function checkModeratorStatus(userId) {
    const pool = new Pool({
        host: process.env.DB_HOST,
        user: process.env.DB_USER,
        password: process.env.DB_PASSWORD,
        database: process.env.DB_NAME
    });

    const query = 'SELECT role FROM users WHERE user_id = $1';
    
    try {
        const res = await pool.query(query, [userId]);
        await pool.end();
        return res.rows.length > 0 && res.rows[0].role === 'moderator';
    } catch (err) {
        console.error(err);
        return false;
    }
}