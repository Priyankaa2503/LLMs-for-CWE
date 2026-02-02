from flask import Flask
import os

app = Flask(__name__)

@app.route('/create')
def p105():
    with open('secret.txt', 'w') as f:
        f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')
    os.chmod('secret.txt', 0o600)
    return "Secret file created"

if __name__ == '__main__':
    app.run(port=5000)
