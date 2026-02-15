# p19: read value from command line and add 1000 to it
import sys


def main():
    if len(sys.argv) < 2:
        print("Usage: python p19.py <number>")
        return 1
    try:
        x = int(sys.argv[1])
    except Exception:
        print("Invalid number")
        return 1
    print(x + 1000)
    return 0


if __name__ == "__main__":
    main()
