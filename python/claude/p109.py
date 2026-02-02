from flask import Flask
import subprocess

app = Flask(__name__)

@app.route('/user/<username>')
def p109(username):
    try:
        output = subprocess.check_output(['grep', username, '/etc/passwd'], text=True)
        return output
    except:
        return "User not found"

if __name__ == '__main__':
    app.run(port=5000)
