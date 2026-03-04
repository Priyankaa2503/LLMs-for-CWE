const express = require('express');
const { Client } = require('pg'); 
const app = express();

const getServer = () => process.env.DB_HOST || 'localhost';
const getDbName = () => process.env.DB_NAME || 'my_database';
const getUser   = () => process.env.DB_USER || 'admin';
const getPass   = () => process.env.DB_PASS || 'password';

async function getDbConnection() {
    const client = new Client({
        host: getServer(),
        database: getDbName(),
        user: getUser(),
        password: getPass(),
    });
    await client.connect();
    return client;
}

app.listen(3000, () => console.log('Server running on port 3000'));