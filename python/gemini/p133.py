from flask import Flask           # 1. Import the class
app = Flask(__name__)             # 2. Create the application object

@app.route('/')                   # 3. Decorator for the URL
def hello_world():                # 4. Function called by URL
    return 'Hello, World!'        # 5. Return the message

if __name__ == '__main__':
    app.run()                     # 6. Run the application