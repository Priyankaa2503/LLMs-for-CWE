import sys

OFFSET = 1000
INT_MIN = -2_147_483_648
INT_MAX = 2_147_483_647


def main() -> None:
    if len(sys.argv) < 2:
        print("Missing argument", file=sys.stderr)
        sys.exit(1)

    try:
        val = int(sys.argv[1], 10)
    except ValueError:
        print("Invalid number", file=sys.stderr)
        sys.exit(1)
        return

    result = val + OFFSET
    if result > INT_MAX or result < INT_MIN:
        print("Overflow risk", file=sys.stderr)
        sys.exit(1)
        return

    print(result)
    sys.exit(0)


if __name__ == "__main__":
    main()
