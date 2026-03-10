# Python (file-like streams)
import html
import re
from urllib.parse import parse_qs, urlsplit

MAX_REQ_BYTES = 8192
MAX_USER_LEN = 32
USERNAME_RE = re.compile(r"^[A-Za-z0-9_-]{1,32}$")

def _read_request_bytes(req_fp) -> bytes:
    data = req_fp.read(MAX_REQ_BYTES)
    if isinstance(data, str):
        data = data.encode("utf-8", "replace")
    return data

def _extract_username(req_bytes: bytes) -> str | None:
    text = req_bytes.decode("utf-8", "replace")

    # Try request line: GET /path?username=... HTTP/1.1
    first_line = text.splitlines()[0] if text else ""
    parts = first_line.split()
    if len(parts) >= 2:
        path = parts[1]
        try:
            qs = parse_qs(urlsplit(path).query, keep_blank_values=False)
            if "username" in qs and qs["username"]:
                return qs["username"][0]
        except Exception:
            pass

    # Try body: username=...
    try:
        if "\r\n\r\n" in text:
            body = text.split("\r\n\r\n", 1)[1]
        elif "\n\n" in text:
            body = text.split("\n\n", 1)[1]
        else:
            body = text
        qs = parse_qs(body, keep_blank_values=False)
        if "username" in qs and qs["username"]:
            return qs["username"][0]
    except Exception:
        return None

    return None

def _valid_username(u: str) -> bool:
    if not isinstance(u, str):
        return False
    if len(u) == 0 or len(u) > MAX_USER_LEN:
        return False
    return USERNAME_RE.match(u) is not None

def _write_response(resp_fp, status_code: int, reason: str, body: str) -> None:
    body_bytes = body.encode("utf-8")
    headers = (
        f"HTTP/1.1 {status_code} {reason}\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "X-Content-Type-Options: nosniff\r\n"
        f"Content-Length: {len(body_bytes)}\r\n"
        "Connection: close\r\n"
        "\r\n"
    ).encode("ascii")
    resp_fp.write(headers)
    resp_fp.write(body_bytes)
    try:
        resp_fp.flush()
    except Exception:
        pass

def http_hello_page(request_fp, response_fp) -> None:
    if request_fp is None or response_fp is None:
        return

    req = _read_request_bytes(request_fp)
    username = _extract_username(req)

    if username is None or not _valid_username(username):
        _write_response(response_fp, 400, "Bad Request", "<!doctype html><html><body>Bad Request</body></html>")
        return

    safe_username = html.escape(username, quote=True)
    body = f"<!doctype html><html><body>Hello {safe_username}</body></html>"
    _write_response(response_fp, 200, "OK", body)