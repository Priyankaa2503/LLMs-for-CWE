# Python
import sys

def main() -> int:
    if len(sys.argv) != 2:
        print("Error: expected exactly one argument.", file=sys.stderr)
        return 1

    input_arg = sys.argv[1]
    print(input_arg)
    trimmed = input_arg.rstrip()
    print(trimmed)
    return 0

if __name__ == "__main__":
    raise SystemExit(main())