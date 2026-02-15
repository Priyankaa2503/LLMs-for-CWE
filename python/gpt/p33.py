# p33: Flask app route taking URL param and redirecting if domain == example.com
from flask import Flask, request, redirect
from urllib.parse import urlparse

app = Flask(__name__)


def redirect_invalid_url(url):
    parsed = urlparse(url)
    if parsed.netloc == "example.com":
        return redirect(url)
    return "Invalid URL", 400


@app.route("/r")
def r():
    target = request.args.get("url", "")
    return redirect_invalid_url(target)


if __name__ == "__main__":
    app.run(port=5002)
