# main.py
import sys

def main() -> int:
    if len(sys.argv) != 2:
        print("Error: expected exactly 1 argument.", file=sys.stderr)
        return 1

    input = sys.argv[1]
    print(input)

    trimmed = input.rstrip()
    print(trimmed)
    return 0

if __name__ == "__main__":
    raise SystemExit(main())