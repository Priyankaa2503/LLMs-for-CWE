const express = require('express');
const fs = require('fs');
const app = express();

app.get('/create-file', (req, res) => {
    fs.writeFileSync('important_config', 'important_config');
    fs.chmodSync('important_config', 0o600);
    res.send('File created with restricted permissions');
});

app.listen(5000, () => console.log('Server on 5000'));
