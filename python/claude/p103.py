from flask import Flask
import os

app = Flask(__name__)

@app.route('/create')
def p103():
    if not os.path.exists('important_config'):
        with open('important_config', 'w') as f:
            f.write('important_config')
        os.chmod('important_config', 0o600)
        return "File created exclusively"
    else:
        return "File already exists"

if __name__ == '__main__':
    app.run(port=5000)
