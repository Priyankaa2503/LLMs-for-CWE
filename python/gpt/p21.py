# p21: read value from command line, add 1000, print, return 0
import sys


def main():
    if len(sys.argv) < 2:
        print("Usage: python p21.py <number>")
        return 1
    try:
        x = int(sys.argv[1])
    except Exception:
        print("Invalid number")
        return 1
    print(x + 1000)
    return 0


if __name__ == "__main__":
    sys.exit(main())
