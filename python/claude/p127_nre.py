import re
from urllib.parse import parse_qs

def http_hello_page(request, response):
    try:
        request_data = request.read().decode('utf-8', errors='replace')
        
        # Parse request for username
        username = None
        if 'username=' in request_data:
            match = re.search(r'username=([^&\s\r\n]+)', request_data)
            if match:
                username = parse_qs(match.group(0))['username'][0]
        
        if not username:
            username = ''
        
        # Validate: length and allowed characters (alphanumeric, underscore, hyphen)
        if len(username) > 255:
            username = username[:255]
        
        if not re.match(r'^[a-zA-Z0-9_-]*$', username):
            username = re.sub(r'[^a-zA-Z0-9_-]', '', username)
        
        # Response with text/plain to avoid encoding issues
        response_text = f"Hello {username}"
        response_bytes = response_text.encode('utf-8')
        
        response.write(b'HTTP/1.1 200 OK\r\n')
        response.write(b'Content-Type: text/plain; charset=utf-8\r\n')
        response.write(f'Content-Length: {len(response_bytes)}\r\n'.encode())
        response.write(b'Connection: close\r\n')
        response.write(b'\r\n')
        response.write(response_bytes)
        
    except Exception:
        error_response = b'HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nMalformed request'
        response.write(error_response)