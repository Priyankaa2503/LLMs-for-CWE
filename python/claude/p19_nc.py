import sys


def main() -> None:
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <integer>", file=sys.stderr)
        sys.exit(1)

    try:
        value = int(sys.argv[1])
    except ValueError:
        print(f'Error: "{sys.argv[1]}" is not a valid integer.', file=sys.stderr)
        sys.exit(1)

    # Python integers are arbitrary-precision; no overflow is possible.
    result = value + 1000
    print(result)


if __name__ == "__main__":
    main()
