from flask import Flask
import os

app = Flask(__name__)

@app.route('/create-file')
def p100():
    with open('important_config', 'w') as f:
        f.write('important_config')
    os.chmod('important_config', 0o600)
    return "File created with restricted permissions"

if __name__ == '__main__':
    app.run(port=5000)
