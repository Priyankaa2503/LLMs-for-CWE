import re
from urllib.parse import parse_qs, urlparse
from io import BytesIO

def http_hello_page(request_stream, response_stream):
    """Secure HTTP handler with XSS and input validation protections"""
    
    # Constants
    MAX_USERNAME_LENGTH = 50
    ALLOWED_CHARS = re.compile(r'^[a-zA-Z0-9._-]*$')
    DEFAULT_USERNAME = "Guest"
    
    try:
        # Parse request line
        request_line = request_stream.readline().decode('utf-8', errors='ignore').strip()
        if not request_line:
            _send_error_response(response_stream, 400, "Bad Request")
            return
        
        parts = request_line.split()
        if len(parts) < 2:
            _send_error_response(response_stream, 400, "Bad Request")
            return
        
        path = parts[1]
        
        # Parse query parameters safely
        parsed_url = urlparse(path)
        query_params = parse_qs(parsed_url.query, keep_blank_values=True)
        username_list = query_params.get('username', [DEFAULT_USERNAME])
        username = username_list[0] if username_list else DEFAULT_USERNAME
        
        # Input validation
        username = _validate_username(username, MAX_USERNAME_LENGTH, ALLOWED_CHARS, DEFAULT_USERNAME)
        
        # Consume remaining headers
        while True:
            line = request_stream.readline()
            if not line or line == b'\r\n' or line == b'\n':
                break
        
        # Build response
        response_body = f"Hello {username}".encode('utf-8')
        response = (
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain; charset=utf-8\r\n"
            "Content-Length: {}\r\n"
            "Cache-Control: no-store\r\n"
            "X-Content-Type-Options: nosniff\r\n"
            "\r\n".format(len(response_body))
        ).encode('utf-8') + response_body
        
        response_stream.write(response)
        response_stream.flush()
        
    except Exception:
        _send_error_response(response_stream, 500, "Internal Server Error")

def _validate_username(username, max_length, allowed_chars, default):
    """Validate username with length and character constraints"""
    username = str(username).strip()
    if not username or len(username) > max_length or not allowed_chars.match(username):
        return default
    return username

def _send_error_response(response_stream, status_code, status_text):
    """Send safe error response"""
    response = (
        f"HTTP/1.1 {status_code} {status_text}\r\n"
        "Content-Type: text/plain; charset=utf-8\r\n"
        "Content-Length: 0\r\n"
        "Cache-Control: no-store\r\n"
        "\r\n"
    ).encode('utf-8')
    response_stream.write(response)
    response_stream.flush()