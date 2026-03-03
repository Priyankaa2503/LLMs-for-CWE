import sys

def main():
    if len(sys.argv) < 2:
        print("Error: No argument provided. Usage: python solution.py <integer>", file=sys.stderr)
        sys.exit(1)

    try:
        value = int(sys.argv[1])
    except ValueError:
        print(f"Error: Invalid integer: '{sys.argv[1]}'", file=sys.stderr)
        sys.exit(1)

    # Python integers have arbitrary precision — no overflow possible
    value += 1000
    print(value)
    return 0

if __name__ == "__main__":
    main()