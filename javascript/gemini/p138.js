const express = require('express');
const { Client } = require('pg');
const app = express();

app.get('/check-moderator/:id', async (req, res) => {
    const client = new Client({ connectionString: 'postgres://localhost/mydb' });
    await client.connect();

    // Execute query
    const result = await client.query('SELECT is_moderator FROM users WHERE id = $1', [req.params.id]);
    
    await client.end();

    // Return result
    const isMod = result.rows.length > 0 ? result.rows[0].is_moderator : false;
    res.json({ userId: req.params.id, isModerator: isMod });
});

app.listen(3000, () => console.log('Server running on port 3000'));