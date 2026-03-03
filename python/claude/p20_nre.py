import sys

# offset defined as a named constant — never a magic number
OFFSET = 1000

# Python int is arbitrary-precision; guard against exceeding 64-bit signed range
# for cross-language consistency and downstream portability.
INT64_MAX = (1 << 63) - 1
INT64_MIN = -(1 << 63)


def main() -> int:
    # verify an argument exists
    if len(sys.argv) != 2:
        print(f"Usage: python {sys.argv[0]} <integer>", file=sys.stderr)
        return 1

    # attempt safe integer parsing
    try:
        value = int(sys.argv[1])
    except ValueError:
        # if parsing fails → exit with an error
        print(f"Error: \"{sys.argv[1]}\" is not a valid integer.", file=sys.stderr)
        return 1

    # before performing value + OFFSET, ensure the result does not exceed the valid range
    result = value + OFFSET
    if result > INT64_MAX:
        print(f"Error: {value} + {OFFSET} would overflow the 64-bit integer range "
              f"(max {INT64_MAX}).", file=sys.stderr)
        return 1
    if result < INT64_MIN:
        print(f"Error: {value} + {OFFSET} would underflow the 64-bit integer range "
              f"(min {INT64_MIN}).", file=sys.stderr)
        return 1

    # if safe, compute and print the result
    print(result)
    return 0


if __name__ == "__main__":
    sys.exit(main())
