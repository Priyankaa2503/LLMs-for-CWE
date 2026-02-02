const express = require('express');
const fs = require('fs');
const app = express();

app.get('/create', (req, res) => {
    fs.writeFileSync('important_config', 'important_config');
    fs.chmodSync('important_config', 0o644);
    res.send('File created with 644 permissions');
});

app.listen(5000, () => console.log('Server on 5000'));
