// JavaScript/Node.js (EJS)
const express = require('express');
const app = express();
const path = require('path');

const ALLOWED_TEMPLATES = new Set(['home.ejs']);

function renderResponseFromEnv(env, req, res) {
    let name = req.query.name || 'Guest';
    
    if (!/^[a-zA-Z0-9_\-\s]{1,100}$/.test(name)) {
        name = 'Guest';
    }
    
    const template = 'home.ejs';
    if (!ALLOWED_TEMPLATES.has(template)) {
        return res.status(403).send('Template not allowed');
    }
    
    res.render(template, { name: name });
}

app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));

app.get('/', (req, res) => {
    renderResponseFromEnv({}, req, res);
});