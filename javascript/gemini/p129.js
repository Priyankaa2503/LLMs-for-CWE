const express = require('express');
const app = express();

function render_response_from_env(env, req) {
    const name = req.query.name || 'Guest';
    // env acts as the template engine/loader
    const template = env.getTemplate('index.html');
    return template.render({ name: name });
}

app.get('/', (req, res) => {
    const response = render_response_from_env(app.env, req);
    res.send(response);
});