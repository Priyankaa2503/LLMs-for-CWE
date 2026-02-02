const express = require('express');
const fs = require('fs');
const app = express();

app.get('/create', (req, res) => {
    fs.writeFileSync('secret.txt', 'U2FsdGVkX1/R+WzJcxgvX/Iw==');
    fs.chmodSync('secret.txt', 0o600);
    res.send('Secret file created');
});

app.listen(5000, () => console.log('Server on 5000'));
