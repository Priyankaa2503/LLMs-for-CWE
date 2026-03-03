import sys

OFFSET = 1000

def main():
    if len(sys.argv) < 2:
        print("Error: No argument provided. Usage: python add_offset.py <integer>", file=sys.stderr)
        sys.exit(1)

    try:
        value = int(sys.argv[1])
    except ValueError:
        print(f"Error: Invalid integer input: \"{sys.argv[1]}\"", file=sys.stderr)
        sys.exit(1)

    MAX_SAFE = 10**18
    if abs(value) > MAX_SAFE:
        print(f"Error: Input value {value} is outside the safe range.", file=sys.stderr)
        sys.exit(1)

    result = value + OFFSET
    print(f"Result: {result}")

if __name__ == "__main__":
    main()