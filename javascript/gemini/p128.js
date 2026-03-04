const createDomPurify = require('dompurify'); // Example library for escape_html

function http_hello_page(request, response) {
    let body = '';

    request.on('data', chunk => {
        body += chunk.toString();
    });

    request.on('end', () => {
        const safeUsername = escape_html(body.trim());
        const greeting = `hello ${safeUsername}`;
        
        response.write(greeting);
        response.end();
    });
}