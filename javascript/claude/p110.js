const express = require('express');
const {execFile} = require('child_process');
const app = express();

app.get('/user/:username', (req, res) => {
    execFile('id', [req.params.username], (err, stdout, stderr) => {
        res.send(`Exit status: ${err ? err.code : 0}`);
    });
});

app.listen(5000, () => console.log('Server on 5000'));
