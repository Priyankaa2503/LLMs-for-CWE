const fs = require('fs');

async function http_hello_page(request, response) {
    let data = '';

    // Read data from the request stream
    for await (const chunk of request) {
        data += chunk;
    }

    const username = data.trim();
    const greeting = `Hello ${username}`;

    // Write the greeting to the response stream
    response.write(greeting);
    response.end();
}