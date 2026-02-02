const express = require('express');
const fs = require('fs');
const app = express();

app.get('/create', (req, res) => {
    const secret = "super secret info";
    const filename = "secret_file.txt";
    fs.writeFileSync(filename, secret);
    fs.chmodSync(filename, 0o400);
    res.send(`Filename: ${filename}`);
});

app.listen(5000, () => console.log('Server on 5000'));
