from flask import Flask
import os

app = Flask(__name__)

@app.route('/create')
def p106():
    secret = "super secret info"
    filename = "secret_file.txt"
    with open(filename, 'w') as f:
        f.write(secret)
    os.chmod(filename, 0o400)
    return f"Filename: {filename}"

if __name__ == '__main__':
    app.run(port=5000)
