# p28: compile regex once, validate target URL, use default if not matching
import re

# compiled once at module load
_ALLOWED_RE = re.compile(r"example\\.com")
DEFAULT_URL = "/default"


def choose_redirect(target):
    if _ALLOWED_RE.search(target or ""):
        return target
    return DEFAULT_URL


if __name__ == "__main__":
    import sys

    target = sys.argv[1] if len(sys.argv) > 1 else None
    print(choose_redirect(target))
