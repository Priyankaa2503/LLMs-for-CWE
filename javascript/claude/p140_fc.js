// JavaScript/Node.js (PostgreSQL with pg library)
const { Pool } = require('pg');

const pool = new Pool({
  user: process.env.DB_USER,
  password: process.env.DB_PASSWORD,
  host: process.env.DB_HOST,
  port: 5432,
  database: process.env.DB_NAME,
  // Least-privilege: dedicated read-only role
});

async function usernameExists(username) {
  // Normalize: trim and validate
  username = username.trim();
  if (!/^[a-zA-Z0-9_]{3,32}$/.test(username)) {
    return false;
  }

  try {
    // Parameterized query with $1 placeholder
    const result = await pool.query(
      'SELECT 1 FROM users WHERE username = $1 LIMIT 1',
      [username]
    );
    
    return result.rows.length > 0;
    
  } catch (error) {
    // Never expose database errors
    console.error('Database error (sanitized)');
    return false;
  }
}

module.exports = { usernameExists };