from flask import Flask
import os

app = Flask(__name__)

@app.route('/create')
def p104():
    with open('important_config', 'w') as f:
        f.write('important_config')
    os.chmod('important_config', 0o700)
    return "File created with 0700 permissions"

if __name__ == '__main__':
    app.run(port=5000)
