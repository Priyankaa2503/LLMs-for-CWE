const { Client } = require('pg');

async function checkUsername(username) {
  const client = new Client({ connectionString: 'your_connection_string' });
  await client.connect();

  const query = 'SELECT 1 FROM users WHERE username = $1';
  const res = await client.query(query, [username]);

  await client.end();
  
  // Returns true if row count is greater than 0
  return res.rowCount > 0;
}