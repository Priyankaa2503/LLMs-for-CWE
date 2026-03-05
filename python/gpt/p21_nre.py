import sys


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

    result = val + 1000
    if result > 2_147_483_647 or result < -2_147_483_648:
        print("Overflow risk", file=sys.stderr)
        sys.exit(1)
        return

    print(result)
    sys.exit(0)


if __name__ == "__main__":
    main()
