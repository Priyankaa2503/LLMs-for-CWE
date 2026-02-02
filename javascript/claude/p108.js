const express = require('express');
const {execFile} = require('child_process');
const app = express();

app.get('/user/:username', (req, res) => {
    execFile('getent', ['passwd', req.params.username], (err, stdout) => {
        if (err) res.send('User not found');
        else res.send(stdout);
    });
});

app.listen(5000, () => console.log('Server on 5000'));
