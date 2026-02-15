# p31: redirect_url uses urllib.parse to parse and check domain
from urllib.parse import urlparse

DEFAULT = "/404"


def redirect_url(url):
    parsed = urlparse(url)
    domain = parsed.netloc
    if domain == "example.com":
        return url  # redirect
    return DEFAULT  # not allowed


if __name__ == "__main__":
    import sys

    if len(sys.argv) < 2:
        print("Usage: p31.py <url>")
    else:
        print(redirect_url(sys.argv[1]))
