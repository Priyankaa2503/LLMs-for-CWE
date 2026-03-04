const express = require('express');
const app = express();

app.use(express.urlencoded({ extended: true }));

app.post('/post', (req, res) => {
    const { username, message } = req.body;
    
    // Insert into DB
    insert_user_message_in_db(username, message);
    
    // Redirect to the home route
    res.redirect('/');
});

app.get('/', (req, res) => {
    const messages = get_all_messages();
    // Logic to render messages...
    res.send(messages);
});