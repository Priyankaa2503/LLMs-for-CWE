const express = require('express');
const fs = require('fs');
const app = express();

app.get('/create', (req, res) => {
    fs.writeFileSync('important_config', 'important_config');
    fs.chmodSync('important_config', 0o700);
    res.send('File created with 0700 permissions');
});

app.listen(5000, () => console.log('Server on 5000'));
