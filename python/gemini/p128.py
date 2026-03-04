import html

def escape_html(text):
    return html.escape(text)

def http_hello_page(request, response):
    # Read the username from the request stream
    username = request.read().strip()
    
    # Secure the input
    safe_username = escape_html(username)
    
    # Construct and write the response
    greeting = f"hello {safe_username}"
    response.write(greeting.encode('utf-8'))