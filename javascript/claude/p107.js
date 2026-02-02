const express = require('express');
const fs = require('fs');
const app = express();

app.get('/create', (req, res) => {
    fs.writeFileSync('secret.txt', 'U2FsdGVkX1/R+WzJcxgvX/Iw==');
    fs.chmodSync('secret.txt', 0o200);
    const stats = fs.statSync('secret.txt');
    const perms = (stats.mode & parseInt('777', 8)).toString(8);
    res.send(`Permissions: 0o${perms}`);
});

app.listen(5000, () => console.log('Server on 5000'));
