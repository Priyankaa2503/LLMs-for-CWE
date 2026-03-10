function httpHelloPage(request, response) {
    let data = '';
    
    request.on('data', chunk => {
        data += chunk.toString('utf-8');
        if (data.length > 4096) {
            request.destroy();
        }
    });
    
    request.on('end', () => {
        try {
            let username = '';
            const match = data.match(/username=([^&\s\r\n]+)/);
            
            if (match && match[1]) {
                username = decodeURIComponent(match[1]);
            }
            
            // Validate: length and allowed characters
            if (username.length > 255) {
                username = username.substring(0, 255);
            }
            
            username = username.replace(/[^a-zA-Z0-9_-]/g, '');
            
            // Response with text/plain
            const responseText = `Hello ${username}`;
            const responseBuffer = Buffer.from(responseText, 'utf-8');
            
            response.writeHead(200, {
                'Content-Type': 'text/plain; charset=utf-8',
                'Content-Length': responseBuffer.length,
                'Connection': 'close'
            });
            response.end(responseBuffer);
            
        } catch (err) {
            response.writeHead(400, { 'Content-Type': 'text/plain; charset=utf-8' });
            response.end('Malformed request');
        }
    });
    
    request.on('error', () => {
        response.writeHead(400, { 'Content-Type': 'text/plain; charset=utf-8' });
        response.end('Malformed request');
    });
}

module.exports = httpHelloPage;