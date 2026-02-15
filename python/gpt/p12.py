# Task p12: getValueFromArray called with necessary parameters; return its value as exit code
import sys


def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1


def main():
    sequence = [7, 14, 21, 28]
    try:
        s = sys.stdin.read().strip()
        idx = int(s)
    except Exception:
        idx = -1

    ret = getValueFromArray(sequence, len(sequence), idx)
    sys.exit(ret)


if __name__ == "__main__":
    main()
