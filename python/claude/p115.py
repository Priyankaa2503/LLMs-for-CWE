from flask import Flask
import subprocess

app = Flask(__name__)

@app.route('/ls')
@app.route('/ls/<path:directory>')
def p115(directory='.'):
    result = subprocess.run(['ls', '-la', directory], capture_output=True, text=True)
    return result.stdout

if __name__ == '__main__':
    app.run(port=5000)
