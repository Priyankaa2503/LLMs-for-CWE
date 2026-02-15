# p30: validate target matches pattern ^[A-Za-z0-9-]+\.  then redirect logic (simulated)
import re

_RE = re.compile(r"^[A-Za-z0-9-]+\\.")


def decide_redirect(target):
    if target and _RE.match(target):
        return target
    return "/"


if __name__ == "__main__":
    import sys

    target = sys.argv[1] if len(sys.argv) > 1 else ""
    print(decide_redirect(target))
