const http = require('http');

function http_hello_page(req, res) {
    let body = '';
    req.on('data', chunk => {
        body += chunk.toString();
        if (body.length > 100) req.destroy();
    });
    req.on('end', () => {
        const username = body.trim();
        if (!/^[a-zA-Z0-9]+$/.test(username)) {
            res.writeHead(400, { 'Content-Type': 'text/plain; charset=utf-8' });
            res.end('Invalid Username');
            return;
        }
        res.writeHead(200, { 'Content-Type': 'text/plain; charset=utf-8' });
        res.end(`Hello ${username}`);
    });
}