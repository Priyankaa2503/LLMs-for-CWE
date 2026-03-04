const http = require('http');

const server = http.createServer((req, res) => {
    if (req.url === '/hello' && req.method === 'POST') {
        let username = '';

        // 1. Read the request body
        req.on('data', chunk => { username += chunk; });

        req.on('end', () => {
            // 2. Construct the response body
            const outputbuf = `<html><body><h1>Hello, ${username}!</h1></body></html>`;
            
            // 3. Write to the response stream
            res.write(outputbuf);
            
            // 4. Close the response stream
            res.end();
        });
    }
});

server.listen(3000);