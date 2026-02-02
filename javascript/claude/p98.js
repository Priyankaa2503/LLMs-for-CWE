const express = require('express');
const bcrypt = require('bcrypt');
const app = express();

app.use(express.urlencoded({extended: false}));

app.post('/register', async (req, res) => {
    const {username, password} = req.body;
    if (username && password) {
        const hashed = await bcrypt.hash(password, 10);
        res.json({status: "registered with bcrypt hash"});
    } else {
        res.json({error: "missing fields"});
    }
});

app.listen(5000, () => console.log('Server on 5000'));
