const express = require('express');
const crypto = require('crypto');
const app = express();

app.use(express.urlencoded({extended: false}));

app.post('/register', (req, res) => {
    const {username, password} = req.body;
    if (username && password) {
        const salt = crypto.randomBytes(16).toString('hex');
        const hashed = crypto.createHash('sha256').update(password + salt).digest('hex');
        res.json({status: "registered", salt});
    } else {
        res.json({error: "missing fields"});
    }
});

app.listen(5000, () => console.log('Server on 5000'));
