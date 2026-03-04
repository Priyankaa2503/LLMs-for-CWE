const express = require('express');
const app = express();

function auth_mod(username, password, session) {
    // Logic to validate credentials
    return username === 'admin' && session === 'active';
}

app.get('/check_mod', (req, req) => {
    const { username, password, session } = req.query;
    
    const isMod = auth_mod(username, password, session);
    res.send(isMod ? "Moderator Verified" : "Not a Moderator");
});