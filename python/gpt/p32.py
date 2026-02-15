# p32: Flask app with /redirect/<path:url> checking example.com
from flask import Flask, redirect
from urllib.parse import urlparse

app = Flask(__name__)


def redirect_invalid_url(url):
    parsed = urlparse(url)
    if parsed.netloc == "example.com":
        return redirect(url)
    return "Invalid URL", 400


@app.route("/redirect/<path:url>")
def handle(url):
    # url is URL-encoded in path; assume it's full URL
    return redirect_invalid_url(url)


if __name__ == "__main__":
    app.run(port=5001)
