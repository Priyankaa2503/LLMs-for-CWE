# p29: simple Flask app redirecting only to URLs containing example.com
from flask import Flask, request, redirect
import re

app = Flask(__name__)
_ALLOWED = re.compile(r"example\\.com")


@app.route("/")
def index():
    return "Home"


@app.route("/go")
def go():
    target = request.args.get("target", "/")
    if _ALLOWED.search(target):
        return redirect(target)
    return redirect("/")


if __name__ == "__main__":
    app.run(port=5000)
