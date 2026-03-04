from flask import Flask
from markupsafe import escape

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    # escape() prevents XSS by converting chars like < to &lt;
    safe_username = escape(username)
    return f"Hello {safe_username}"