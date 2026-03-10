// JavaScript (Node.js + Express + Handlebars)
const express = require('express');
const handlebars = require('handlebars');
const app = express();

// Fixed templates (immutable)
const TEMPLATES = {
    'default': 'Hello, {{name}}!'
};

function renderResponseFromEnv(env) {
    // Get template name from env (fixed allocation)
    const templateName = process.env.TEMPLATE_NAME || 'default';
    const templateStr = TEMPLATES[templateName] || '';
    
    if (!templateStr) {
        return { html: 'Error: Invalid template', status: 500 };
    }
    
    // Retrieve 'name' from query params
    let name = (new URL(env.request.url, 'http://localhost')).searchParams.get('name') || 'Guest';
    
    // Length validation: max 50 chars
    if (name.length > 50) {
        name = 'Guest';
    }
    
    // Charset validation: alphanumeric, spaces, hyphens, apostrophes
    if (!/^[a-zA-Z0-9\s\-']*$/.test(name)) {
        name = 'Guest';
    }
    
    // Compile and render with Handlebars (auto-escapes by default)
    const template = handlebars.compile(templateStr);
    const html = template({ name });
    
    return { html, status: 200 };
}

function home(req, res) {
    const result = renderResponseFromEnv({ request: req });
    res.status(result.status).send(result.html);
}

app.get('/', home);
app.listen(3000);