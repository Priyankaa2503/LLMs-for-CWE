import io

def http_hello_page(request: io.RawIOBase, response: io.RawIOBase):
    # Read username from the request stream
    username = request.read().decode('utf-8').strip()
    
    # Construct the message
    message = f"Hello {username}"
    
    # Write to the response stream
    response.write(message.encode('utf-8'))