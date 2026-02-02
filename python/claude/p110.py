from flask import Flask
import subprocess

app = Flask(__name__)

@app.route('/user/<username>')
def p110(username):
    result = subprocess.run(['id', username], capture_output=True)
    return f"Exit status: {result.returncode}"

if __name__ == '__main__':
    app.run(port=5000)
