import sys

OFFSET = 1000

def main():
    # Verify an argument exists
    if len(sys.argv) < 2:
        print("Error: No argument provided.", file=sys.stderr)
        sys.exit(1)

    try:
        # Attempt safe integer parsing
        value = int(sys.argv[1])

        # Before performing value + 1000, ensure the result does not exceed the valid integer range
        # Python handles arbitrarily large integers, but for the sake of the prompt's "safe pattern":
        MAX_INT = sys.maxsize
        if value > MAX_INT - OFFSET:
             print("Error: Integer overflow (simulated limit).", file=sys.stderr)
             sys.exit(1)

        # If safe, compute and print the result
        print(value + OFFSET)

    except ValueError:
        # If parsing fails, exit with an error
        print("Error: Invalid number format.", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
