import re
import html
from urllib.parse import parse_qs, urlparse

def http_hello_page(request, response):
    """
    Handles HTTP request and sends a hello response with username.
    """
    try:
        # Parse request line
        request_data = request.read(4096).decode('utf-8', errors='replace')
        
        if not request_data:
            send_error_response(response, 400, "Empty request")
            return
        
        # Extract request line
        lines = request_data.split('\r\n')
        request_line = lines[0].split()
        
        if len(request_line) < 2:
            send_error_response(response, 400, "Invalid request format")
            return
        
        method = request_line[0]
        path = request_line[1]
        
        # Extract username from query string or POST body
        username = None
        
        if method == 'GET':
            parsed_url = urlparse(path)
            query_params = parse_qs(parsed_url.query)
            username = query_params.get('username', [None])[0]
        elif method == 'POST':
            body = lines[-1] if lines[-1] else ""
            query_params = parse_qs(body)
            username = query_params.get('username', [None])[0]
        
        # Validate username
        if not username:
            send_error_response(response, 400, "Missing username parameter")
            return
        
        if not is_valid_username(username):
            send_error_response(response, 400, "Invalid username format")
            return
        
        # Create response with proper headers and HTML encoding
        safe_username = html.escape(username)
        body = f"Hello {safe_username}"
        
        # Send response
        response_headers = (
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=utf-8\r\n"
            f"Content-Length: {len(body.encode('utf-8'))}\r\n"
            "Connection: close\r\n"
            "\r\n"
        )
        
        response.write(response_headers.encode('utf-8'))
        response.write(body.encode('utf-8'))
        response.flush()
        
    except Exception as e:
        send_error_response(response, 500, "Internal server error")

def is_valid_username(username):
    """Validate username: length 1-100, alphanumeric/underscore/hyphen only"""
    if not isinstance(username, str):
        return False
    if len(username) < 1 or len(username) > 100:
        return False
    return bool(re.match(r'^[a-zA-Z0-9_-]+$', username))

def send_error_response(response, status_code, message):
    """Send error response"""
    status_text = {400: "Bad Request", 500: "Internal Server Error"}.get(status_code, "Error")
    body = f"Error {status_code}: {message}"
    headers = (
        f"HTTP/1.1 {status_code} {status_text}\r\n"
        "Content-Type: text/plain; charset=utf-8\r\n"
        f"Content-Length: {len(body.encode('utf-8'))}\r\n"
        "Connection: close\r\n"
        "\r\n"
    )
    response.write(headers.encode('utf-8'))
    response.write(body.encode('utf-8'))
    response.flush()