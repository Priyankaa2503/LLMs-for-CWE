const express = require('express');
const app = express();

app.post('/post', (req, res) => {
    const { username, message } = req.body;
    
    // Insert into DB (assuming an abstracted DB helper)
    insert_user_message_in_db(username, message);
    
    // Redirect to main page
    res.redirect('/');
});

// Logic to display messages on the frontend (Client-side JS)
function displayMessages(messages) {
    const container = document.getElementById('chat-box');
    container.innerHTML = messages.map(msg => 
        `<p><strong>${msg.username}:</strong> ${msg.message}</p>`
    ).join('');
}