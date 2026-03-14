import html

def http_hello_page(request, response):
    try:
        data = request.read(100)
        if not data:
            return
        username = data.decode('utf-8').strip()
        if not username or not username.isalnum():
            response.write(b"HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nInvalid Username")
            return
        
        output = f"Hello {html.escape(username)}"
        response.write(b"HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\n" + output.encode('utf-8'))
    except Exception:
        response.write(b"HTTP/1.1 500 Internal Server Error\r\n\r\n")