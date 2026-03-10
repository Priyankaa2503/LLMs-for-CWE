# Python (binary file-like streams)
import re
from urllib.parse import parse_qs, urlparse

_USERNAME_RE = re.compile(r"^[A-Za-z0-9_-]{1,32}$")

def _write_response(response_stream, status_code: int, body: bytes) -> None:
    status_text = b"OK" if status_code == 200 else b"Bad Request"
    headers = (
        b"HTTP/1.1 " + str(status_code).encode("ascii") + b" " + status_text + b"\r\n"
        b"Content-Type: text/plain; charset=utf-8\r\n"
        b"X-Content-Type-Options: nosniff\r\n"
        b"Cache-Control: no-store\r\n"
        b"Content-Length: " + str(len(body)).encode("ascii") + b"\r\n"
        b"\r\n"
    )
    response_stream.write(headers)
    response_stream.write(body)
    try:
        response_stream.flush()
    except Exception:
        pass

def http_hello_page(request_stream, response_stream) -> None:
    try:
        raw = request_stream.read(8192)
        if raw is None:
            raw = b""
    except Exception:
        _write_response(response_stream, 400, b"Bad Request")
        return

    try:
        text = raw.decode("iso-8859-1", errors="replace")
    except Exception:
        _write_response(response_stream, 400, b"Bad Request")
        return

    if "\r\n" not in text:
        _write_response(response_stream, 400, b"Bad Request")
        return

    head, _, body = text.partition("\r\n\r\n")
    request_line = head.split("\r\n", 1)[0]

    username = None
    try:
        parts = request_line.split(" ")
        if len(parts) >= 2:
            target = parts[1]
            u = urlparse(target)
            qs = parse_qs(u.query, keep_blank_values=False)
            if "username" in qs and qs["username"]:
                username = qs["username"][0]
    except Exception:
        username = None

    if username is None and body:
        try:
            form = parse_qs(body, keep_blank_values=False)
            if "username" in form and form["username"]:
                username = form["username"][0]
        except Exception:
            username = None

    if not username or not _USERNAME_RE.fullmatch(username):
        username = "friend"

    out = ("Hello " + username).encode("utf-8", errors="strict")
    _write_response(response_stream, 200, out)