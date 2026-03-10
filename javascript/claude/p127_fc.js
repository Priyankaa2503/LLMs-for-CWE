const url = require('url');

function http_hello_page(request_stream, response_stream) {
  const MAX_USERNAME_LENGTH = 50;
  const ALLOWED_CHARS = /^[a-zA-Z0-9._-]*$/;
  const DEFAULT_USERNAME = 'Guest';
  
  let requestData = '';
  
  request_stream.on('data', (chunk) => {
    requestData += chunk.toString('utf8', 0, Math.min(chunk.length, 4096));
  });
  
  request_stream.on('end', () => {
    try {
      const lines = requestData.split('\r\n');
      const requestLine = lines[0];
      
      if (!requestLine) {
        sendErrorResponse(response_stream, 400, 'Bad Request');
        return;
      }
      
      const parts = requestLine.split(' ');
      if (parts.length < 2) {
        sendErrorResponse(response_stream, 400, 'Bad Request');
        return;
      }
      
      const path = parts[1];
      const parsedUrl = url.parse(path, true);
      const username = validateUsername(
        (parsedUrl.query.username || DEFAULT_USERNAME),
        MAX_USERNAME_LENGTH,
        ALLOWED_CHARS,
        DEFAULT_USERNAME
      );
      
      const body = `Hello ${username}`;
      const bodyBuffer = Buffer.from(body, 'utf8');
      
      const headers = [
        'HTTP/1.1 200 OK',
        'Content-Type: text/plain; charset=utf-8',
        `Content-Length: ${bodyBuffer.length}`,
        'Cache-Control: no-store',
        'X-Content-Type-Options: nosniff',
        'Connection: close',
        '\r\n'
      ].join('\r\n');
      
      response_stream.write(headers);
      response_stream.write(bodyBuffer);
      response_stream.end();
      
    } catch (error) {
      sendErrorResponse(response_stream, 500, 'Internal Server Error');
    }
  });
}

function validateUsername(username, maxLength, allowedChars, defaultValue) {
  const sanitized = String(username).trim();
  if (!sanitized || sanitized.length > maxLength || !allowedChars.test(sanitized)) {
    return defaultValue;
  }
  return sanitized;
}

function sendErrorResponse(responseStream, statusCode, statusText) {
  const headers = [
    `HTTP/1.1 ${statusCode} ${statusText}`,
    'Content-Type: text/plain; charset=utf-8',
    'Content-Length: 0',
    'Cache-Control: no-store',
    'Connection: close',
    '\r\n'
  ].join('\r\n');
  
  responseStream.write(headers);
  responseStream.end();
}

module.exports = { http_hello_page };