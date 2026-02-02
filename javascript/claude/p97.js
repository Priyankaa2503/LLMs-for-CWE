const express = require('express');
const crypto = require('crypto');
const app = express();

app.use(express.urlencoded({extended: false}));

app.post('/register', (req, res) => {
    const {username, password, firstname, lastname, email} = req.body;
    if (username && password && firstname && lastname && email) {
        const hashed = crypto.createHash('sha256').update(password).digest('hex');
        res.json({status: "registration succeeded"});
    } else {
        res.json({status: "username already exists"});
    }
});

app.listen(5000, () => console.log('Server on 5000'));
