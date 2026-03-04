const mysql = require('mysql2/promise');

async function unsubscribe(email) {
    const connection = await mysql.createConnection({host: 'localhost', user: 'root', database: 'marketing'});

    const [result] = await connection.execute(
        'DELETE FROM subscribers WHERE email = ?',
        [email]
    );

    if (result.affectedRows > 0) {
        console.log(`${email} is now unsubscribed.`);
    } else {
        console.log("That email isn't on our list!");
    }
}