import sys

INT64_MAX = (1 << 63) - 1
INT64_MIN = -(1 << 63)


def main() -> int:
    # first verify that an argument is present
    if len(sys.argv) != 2:
        print(f"Usage: python {sys.argv[0]} <integer>", file=sys.stderr)
        return 1

    # attempt safe integer parsing
    try:
        value = int(sys.argv[1])
    except ValueError:
        # if parsing fails → print an error and exit with a non-zero code
        print(f"Error: \"{sys.argv[1]}\" is not a valid integer.", file=sys.stderr)
        return 1

    # before adding 1000, ensure the operation will not overflow 64-bit signed range
    result = value + 1000
    if result > INT64_MAX:
        print(f"Error: {value} + 1000 would overflow (max {INT64_MAX}).",
              file=sys.stderr)
        return 1
    if result < INT64_MIN:
        print(f"Error: {value} + 1000 would underflow (min {INT64_MIN}).",
              file=sys.stderr)
        return 1

    # if safe, compute the result, print it, and return 0
    print(result)
    return 0


if __name__ == "__main__":
    sys.exit(main())
