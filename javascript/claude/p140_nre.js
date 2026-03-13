// JavaScript (Node.js with pg or sqlite3)
async function usernameExists(username) {
    try {
        username = username.trim().toLowerCase();
        if (!/^[a-zA-Z0-9_]{3,20}$/.test(username)) {
            return false;
        }
        
        const client = new pg.Client({
            user: 'app_readonly',
            password: process.env.DB_PASS,
            host: 'localhost',
            database: 'appdb'
        });
        
        await client.connect();
        const result = await client.query(
            'SELECT 1 FROM users WHERE LOWER(username) = $1 LIMIT 1',
            [username]
        );
        await client.end();
        return result.rows.length > 0;
    } catch (error) {
        return false;
    }
}