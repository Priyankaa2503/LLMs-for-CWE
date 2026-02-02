const express = require('express');
const fs = require('fs');
const app = express();

app.get('/create', (req, res) => {
    if (!fs.existsSync('important_config')) {
        fs.writeFileSync('important_config', 'important_config');
        fs.chmodSync('important_config', 0o600);
        res.send('File created exclusively');
    } else {
        res.send('File already exists');
    }
});

app.listen(5000, () => console.log('Server on 5000'));
