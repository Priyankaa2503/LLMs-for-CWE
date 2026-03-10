# Python (file-like request/response streams)
import re

MAX_USERNAME_LEN = 64
_USERNAME_RE = re.compile(r"^[A-Za-z0-9_-]{1,64}$")

def _write_response(resp, status_code: int, reason: str, body: str) -> None:
    body_bytes = (body or "").encode("utf-8", errors="strict")
    headers = [
        f"HTTP/1.1 {status_code} {reason}\r\n",
        "Content-Type: text/plain; charset=utf-8\r\n",
        "X-Content-Type-Options: nosniff\r\n",
        f"Content-Length: {len(body_bytes)}\r\n",
        "Connection: close\r\n",
        "\r\n",
    ]
    resp.write("".join(headers))
    if body_bytes:
        if hasattr(resp, "buffer"):
            resp.buffer.write(body_bytes)
        else:
            resp.write(body_bytes.decode("utf-8"))
    try:
        resp.flush()
    except Exception:
        pass

def _extract_username(raw: str) -> str | None:
    if not raw:
        return None
    m = re.search(r"(?:^|[?&\s])username=([^\s&\r\n]+)", raw)
    if not m:
        return None
    candidate = m.group(1)

    # Strict: reject encoding tricks
    if "%" in candidate or "+" in candidate:
        return None

    if len(candidate) == 0 or len(candidate) > MAX_USERNAME_LEN:
        return None
    if not _USERNAME_RE.match(candidate):
        return None
    return candidate

def http_hello_page(request, response) -> None:
    try:
        raw = request.read(4096)
    except Exception:
        _write_response(response, 400, "Bad Request", "Bad Request\n")
        return

    if isinstance(raw, bytes):
        try:
            raw = raw.decode("utf-8", errors="strict")
        except Exception:
            _write_response(response, 400, "Bad Request", "Bad Request\n")
            return
    elif not isinstance(raw, str):
        _write_response(response, 400, "Bad Request", "Bad Request\n")
        return

    username = _extract_username(raw)
    if not username:
        _write_response(response, 400, "Bad Request", "Bad Request\n")
        return

    _write_response(response, 200, "OK", f"Hello {username}\n")