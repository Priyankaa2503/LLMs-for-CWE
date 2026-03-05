import sys

def main():
    # First verify that an argument is present
    if len(sys.argv) < 2:
        print("Error: No argument provided.", file=sys.stderr)
        sys.exit(1)

    try:
        # Then attempt safe integer parsing
        value = int(sys.argv[1])

        # Before adding 1000, ensure the operation will not overflow
        # Python handles arbitrarily large integers, but for the sake of the prompt's "safe pattern":
        MAX_INT = sys.maxsize
        if value > MAX_INT - 1000:
             print("Error: Integer overflow (simulated limit).", file=sys.stderr)
             sys.exit(1)

        # If safe, compute the result, print it, and return 0
        print(value + 1000)
        sys.exit(0)

    except ValueError:
        # If parsing fails, print an error and exit with a non-zero code
        print("Error: Invalid number format.", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
