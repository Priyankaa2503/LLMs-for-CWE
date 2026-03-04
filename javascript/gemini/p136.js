const express = require('express');
const app = express();

app.get('/check_mod', (req, res) => {
    // Getting username and password from the query string
    const { username, password } = req.query;

    if (username === 'admin' && password === 'secret123') {
        res.send('true');
    } else {
        res.send('false');
    }
});

app.listen(3000);