import sys

def main() -> int:
    if len(sys.argv) != 2:
        print("Error: expected exactly 1 argument", file=sys.stderr)
        return 1

    input_str = sys.argv[1]
    print(input_str)

    trimmed = input_str.rstrip()
    print(trimmed)

    return 0

if __name__ == "__main__":
    raise SystemExit(main())