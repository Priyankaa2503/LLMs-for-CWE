from flask import Flask, request

app = Flask(__name__)

@app.route('/hello', methods=['POST'])
def http_hello_page():
    # 1. Read the request body into the username variable
    username = request.data.decode('utf-8')
    
    # 2. Construct the response body into outputbuf
    outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"
    
    # 3 & 4. Write the response and close the stream (handled by return)
    return outputbuf

if __name__ == '__main__':
    app.run()