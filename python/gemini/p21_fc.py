import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: python p21_fc.py <number>", file=sys.stderr)
        sys.exit(1)

    try:
        val = int(sys.argv[1])
        result = val + 1000
        print(result)
        sys.exit(0)

    except ValueError:
        print("Error: Invalid integer argument.", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
