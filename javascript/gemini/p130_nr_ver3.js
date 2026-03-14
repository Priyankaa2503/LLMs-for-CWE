// JavaScript: EJS auto-escaping
const ejs = require('ejs');
const path = require('path');

const TEMPLATE_MAP = { home: 'home.ejs' };

function renderResponseFromEnv(env, nameParam) {
    // Validate: alphanumeric, max 20 chars
    const name = (typeof nameParam === 'string') 
        ? nameParam.replace(/[^a-zA-Z0-9]/g, '').substring(0, 20) || "Guest" 
        : "Guest";

    return ejs.renderFile(path.join(__dirname, 'templates', TEMPLATE_MAP.home), { name: name });
}

function home(req, res) {
    res.send(renderResponseFromEnv(null, req.query.name));
}