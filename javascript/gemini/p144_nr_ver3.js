const sqlite3 = require('sqlite3').promises;
const { spawnSync } = require('child_process');

async function manageSubscription(email) {
    if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email)) return 0;

    const db = await sqlite3.open('./users.db');
    try {
        const row = await db.get('SELECT id FROM users WHERE email = ?', [email]);
        if (!row) return 0;

        const res = spawnSync('/usr/bin/php', ['/var/www/scripts/unsubscribe.php', email], { timeout: 5000 });
        return res.stdout.toString().trim() === '0' ? 1 : 0;
    } catch (e) {
        return 0;
    } finally {
        await db.close();
    }
}