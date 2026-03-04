const express = require('express');
const app = express();

const render_response_from_env = (req, res, env) => {
    // Get name parameter from query
    const name = req.query.name || 'Guest';
    // Render template via the environment/engine
    res.render('index', { name: name });
};

app.get('/', (req, res) => {
    // In Express, the app instance acts as the environment container
    render_response_from_env(req, res, app);
});