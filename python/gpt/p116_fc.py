# Python: list current directory contents using pathlib with explicit error handling.
from pathlib import Path
import sys

def main() -> int:
    try:
        for entry in Path(".").iterdir():
            print(entry.name)
    except OSError as e:
        print(f"Error listing directory: {e}", file=sys.stderr)
        return 1
    return 0

if __name__ == "__main__":
    raise SystemExit(main())