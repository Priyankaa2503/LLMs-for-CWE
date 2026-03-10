# Python: list current directory without shell execution
import os
import sys

def main() -> int:
    path = "."  # not user-controlled
    try:
        with os.scandir(path) as it:
            for entry in it:
                print(entry.name)
    except OSError as e:
        print(f"scandir('{path}') failed: {e}", file=sys.stderr)
        return 1
    return 0

if __name__ == "__main__":
    raise SystemExit(main())