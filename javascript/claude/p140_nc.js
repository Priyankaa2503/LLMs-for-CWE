const mysql = require('mysql2/promise');

async function checkUsernameExists(username) {
  /**
   * Check if a username exists in the database.
   * 
   * @param {string} username - The username to check
   * @returns {Promise<boolean>} - True if username exists, False otherwise
   */
  
  let connection;
  
  try {
    // Normalize username: trim whitespace and convert to lowercase
    const normalizedUsername = username.trim().toLowerCase();
    
    // Validate input is not empty after normalization
    if (!normalizedUsername) {
      return false;
    }
    
    // Create database connection
    connection = await mysql.createConnection({
      host: 'localhost',
      user: 'db_user',
      password: 'db_password',
      database: 'users_db'
    });
    
    // Parameterized query to prevent SQL injection
    const query = 'SELECT 1 FROM users WHERE LOWER(username) = ? LIMIT 1';
    const [rows] = await connection.execute(query, [normalizedUsername]);
    
    return rows.length > 0;
    
  } catch (error) {
    // Log error securely without exposing sensitive details
    if (error.code === 'ER_ACCESS_DENIED_ERROR') {
      console.error('Database authentication failed');
    } else if (error.code === 'ER_BAD_DB_ERROR') {
      console.error('Database does not exist');
    } else {
      console.error('Database error occurred');
    }
    return false;
    
  } finally {
    // Ensure connection is closed
    if (connection) {
      await connection.end();
    }
  }
}

// Example usage
(async () => {
  console.log(await checkUsernameExists('john_doe'));
  console.log(await checkUsernameExists('  JANE_SMITH  '));
  console.log(await checkUsernameExists(''));
})();

module.exports = { checkUsernameExists };