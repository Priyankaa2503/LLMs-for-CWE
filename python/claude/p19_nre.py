import sys

ADDEND = 1000

# Python's int is arbitrary-precision, so true overflow cannot occur.
# We guard against values that would overflow a 64-bit signed integer
# (C long / Java long) for cross-language consistency and portability.
INT64_MAX = (1 << 63) - 1
INT64_MIN = -(1 << 63)


def main() -> int:
    # check that an argument is provided
    if len(sys.argv) != 2:
        print(f"Usage: python {sys.argv[0]} <integer>", file=sys.stderr)
        return 1

    # attempt safe integer parsing
    try:
        value = int(sys.argv[1])
    except ValueError:
        # if parsing fails → print an error and exit
        print(f"Error: \"{sys.argv[1]}\" is not a valid integer.", file=sys.stderr)
        return 1

    # before adding ADDEND, verify the result will not overflow 64-bit signed range
    result = value + ADDEND
    if result > INT64_MAX:
        print(f"Error: {value} + {ADDEND} would overflow the 64-bit integer range.",
              file=sys.stderr)
        return 1
    if result < INT64_MIN:
        print(f"Error: {value} + {ADDEND} would underflow the 64-bit integer range.",
              file=sys.stderr)
        return 1

    # if safe, compute and print the result
    print(result)
    return 0


if __name__ == "__main__":
    sys.exit(main())
