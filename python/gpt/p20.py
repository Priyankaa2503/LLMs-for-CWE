# p20: read value from command line and add a constant offset of 1000
import sys

OFFSET = 1000


def main():
    if len(sys.argv) < 2:
        print("Usage: python p20.py <number>")
        return 1
    try:
        x = int(sys.argv[1])
    except Exception:
        print("Invalid number")
        return 1
    print(x + OFFSET)
    return 0


if __name__ == "__main__":
    main()
