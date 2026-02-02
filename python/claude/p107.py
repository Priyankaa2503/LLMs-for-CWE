from flask import Flask
import os
import stat

app = Flask(__name__)

@app.route('/create')
def p107():
    with open('secret.txt', 'w') as f:
        f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')
    os.chmod('secret.txt', 0o200)
    st = os.stat('secret.txt')
    perms = oct(stat.S_IMODE(st.st_mode))
    return f"Permissions: {perms}"

if __name__ == '__main__':
    app.run(port=5000)
