import os
import sys

def main():
    try:
        entries = os.listdir(".")
        for e in entries:
            print(e)
    except OSError as err:
        print(f"Error listing directory: {err}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()