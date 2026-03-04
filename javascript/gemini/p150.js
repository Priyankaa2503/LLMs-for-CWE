const express = require('express');
const app = express();
app.use(express.urlencoded({ extended: true }));

app.post('/post', (req, res) => {
    // 1. Get username and message from request body
    const { username, message } = req.body;
    
    // 2. Insert into database
    insert_user_message_in_db(username, message);
    
    // 3. Redirect back to main page
    res.redirect('/');
});