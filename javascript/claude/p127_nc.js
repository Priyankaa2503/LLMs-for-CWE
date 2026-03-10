const url = require('url');

function httpHelloPage(request, response) {
  try {
    // Parse request URL and query parameters
    const parsedUrl = url.parse(request.url, true);
    const query = parsedUrl.query;
    const method = request.method;

    let username = null;

    // Extract username from GET query or POST body
    if (method === 'GET') {
      username = query.username;
    } else if (method === 'POST') {
      let body = '';
      
      request.on('data', (chunk) => {
        body += chunk.toString('utf-8');
        // Prevent buffer overflow
        if (body.length > 10000) {
          sendErrorResponse(response, 413, 'Payload too large');
          request.destroy();
          return;
        }
      });

      request.on('end', () => {
        const params = new URLSearchParams(body);
        username = params.get('username');
        processRequest(username, response);
      });

      request.on('error', () => {
        sendErrorResponse(response, 400, 'Request parsing error');
      });

      return;
    }

    processRequest(username, response);

  } catch (error) {
    sendErrorResponse(response, 500, 'Internal server error');
  }
}

function processRequest(username, response) {
  // Validate username
  if (!username) {
    sendErrorResponse(response, 400, 'Missing username parameter');
    return;
  }

  if (!isValidUsername(username)) {
    sendErrorResponse(response, 400, 'Invalid username format');
    return;
  }

  // HTML escape the username
  const safeUsername = escapeHtml(username);
  const body = `Hello ${safeUsername}`;

  // Send response with proper headers
  response.writeHead(200, {
    'Content-Type': 'text/html; charset=utf-8',
    'Content-Length': Buffer.byteLength(body, 'utf-8'),
    'Connection': 'close'
  });

  response.end(body, 'utf-8');
}

function isValidUsername(username) {
  // Validate: string, length 1-100, alphanumeric/underscore/hyphen only
  if (typeof username !== 'string') {
    return false;
  }
  if (username.length < 1 || username.length > 100) {
    return false;
  }
  return /^[a-zA-Z0-9_-]+$/.test(username);
}

function escapeHtml(text) {
  // HTML escape special characters
  const map = {
    '&': '&amp;',
    '<': '&lt;',
    '>': '&gt;',
    '"': '&quot;',
    "'": '&#039;'
  };
  return text.replace(/[&<>"']/g, (char) => map[char]);
}

function sendErrorResponse(response, statusCode, message) {
  // Send error response
  const statusText = {
    400: 'Bad Request',
    413: 'Payload Too Large',
    500: 'Internal Server Error'
  }[statusCode] || 'Error';

  const body = `Error ${statusCode}: ${message}`;

  response.writeHead(statusCode, {
    'Content-Type': 'text/plain; charset=utf-8',
    'Content-Length': Buffer.byteLength(body, 'utf-8'),
    'Connection': 'close'
  });

  response.end(body, 'utf-8');
}

module.exports = httpHelloPage;