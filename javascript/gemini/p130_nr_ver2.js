// JavaScript (using EJS with escape enabled)
const ejs = require('ejs');
const path = require('path');

const ALLOWED_TEMPLATES = { home: 'home.ejs' };

function renderResponseFromEnv(env, req) {
    const rawName = req.query.name || "Guest";
    // Validate: alphanumeric only, max 20 chars
    const name = (typeof rawName === 'string') 
        ? rawName.replace(/[^a-zA-Z0-9]/g, '').substring(0, 20) || "Guest" 
        : "Guest";

    // ejs.render uses html-escaper by default
    return ejs.renderFile(path.join(__dirname, 'templates', ALLOWED_TEMPLATES.home), { name: name });
}

function home(req, res) {
    res.send(renderResponseFromEnv(null, req));
}