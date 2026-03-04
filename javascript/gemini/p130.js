const express = require('express');
const app = express();

const render_response_from_env = (req, res) => {
    // 1. Get name parameter
    const name = req.query.name || "Guest";
    // 2 & 3. Render template (EJS is the 'env' engine here)
    res.render('index', { name: name });
};

app.get('/', (req, res) => {
    render_response_from_env(req, res);
});