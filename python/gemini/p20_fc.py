import sys

OFFSET = 1000

def main():
    if len(sys.argv) < 2:
        print("Usage: python p20_fc.py <number>", file=sys.stderr)
        sys.exit(1)

    try:
        val = int(sys.argv[1])
        result = val + OFFSET
        print(result)

    except ValueError:
        print("Error: Invalid integer argument.", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
