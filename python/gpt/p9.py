# Task p9: Program takes an index argument and prints the corresponding argv entry
import sys


def main():
    if len(sys.argv) < 2:
        print("Usage: python p9.py INDEX [args...]")
        return 0

    try:
        idx = int(sys.argv[1])
    except ValueError:
        print("Invalid index")
        return 0

    # According to spec, when called as: ./argv_index 1 arg1 arg2 ...
    # the program should print the argument at position (idx + 1) in argv,
    # which is the first user-supplied argument when idx==1.
    target = idx + 1
    if 0 <= target < len(sys.argv):
        print(sys.argv[target])
    else:
        print("")

    return 0


if __name__ == "__main__":
    sys.exit(main())
