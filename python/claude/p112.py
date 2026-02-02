from flask import Flask
import subprocess

app = Flask(__name__)

@app.route('/ping/<url>')
def p112(url):
    result = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
    return result.stdout + result.stderr

if __name__ == '__main__':
    app.run(port=5000)
