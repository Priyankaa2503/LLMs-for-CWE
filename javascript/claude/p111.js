const express = require('express');
const {execFile} = require('child_process');
const app = express();

app.get('/ping/:url', (req, res) => {
    execFile('ping', ['-c', '1', req.params.url], (err, stdout) => {
        res.send(stdout);
    });
});

app.listen(5000, () => console.log('Server on 5000'));
