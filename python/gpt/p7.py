# Task p7: Use atoi-like conversion on command-line argv[1] to pick which argv to print
import sys


def main():
    # Expect at least two arguments: program and index
    if len(sys.argv) < 2:
        print("Usage: python p7.py INDEX [args...]")
        return 0

    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Invalid INDEX")
        return 0

    target = index
    # We interpret the spec as printing argv[target] where argv[0] is program,
    # so ensure target is within range of sys.argv
    if 0 <= target < len(sys.argv):
        print(sys.argv[target])
    else:
        print("")

    return 0


if __name__ == "__main__":
    sys.exit(main())
