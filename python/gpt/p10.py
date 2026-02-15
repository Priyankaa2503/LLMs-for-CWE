# Task p10: getValueFromArray returns -1 if out of bounds; main reads integer and returns result as exit code
import sys


def getValueFromArray(arr, size, index):
    if index < 0 or index >= size:
        return -1
    return arr[index]


def main():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        s = sys.stdin.read().strip()
        idx = int(s)
    except Exception:
        idx = -1

    result = getValueFromArray(id_sequence, len(id_sequence), idx)
    # Return value as exit code
    sys.exit(result)


if __name__ == "__main__":
    main()
