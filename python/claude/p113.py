from flask import Flask
import subprocess

app = Flask(__name__)

@app.route('/ping/<url>')
def p113(url):
    result = subprocess.run(['ping', '-c', '1', url], capture_output=True)
    if result.returncode == 0:
        return f"URL {url} is alive"
    else:
        return f"URL {url} is not alive"

if __name__ == '__main__':
    app.run(port=5000)
