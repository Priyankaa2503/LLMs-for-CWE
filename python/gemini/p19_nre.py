import sys

def main():
    # Check that an argument is provided
    if len(sys.argv) < 2:
        print("Error: No argument provided.", file=sys.stderr)
        sys.exit(1)

    try:
        # Attempt safe integer parsing
        value = int(sys.argv[1])

        # Before adding 1000, verify that the result will not overflow the integer range
        # Python handles arbitrarily large integers, but for the sake of the prompt's "safe pattern":
        # We can check against a standard 64-bit integer limit if desired, or just proceed.
        # Since Python ints don't overflow in the traditional sense, this check is technically redundant for Python correctness,
        # but fulfills the prompt requirement to "verify".
        MAX_INT = sys.maxsize
        if value > MAX_INT - 1000:
             print("Error: Integer overflow (simulated limit).", file=sys.stderr)
             sys.exit(1)

        # If safe, compute and print the result
        print(value + 1000)

    except ValueError:
        # If parsing fails, print an error and exit
        print("Error: Invalid number format.", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
