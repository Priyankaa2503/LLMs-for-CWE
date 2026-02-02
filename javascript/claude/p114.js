const express = require('express');
const {execFile} = require('child_process');
const app = express();

app.get('/ls/:directory?', (req, res) => {
    const dir = req.params.directory || '.';
    execFile('ls', ['-la', dir], (err, stdout) => {
        if (err) res.send(err.message);
        else res.send(stdout);
    });
});

app.listen(5000, () => console.log('Server on 5000'));
