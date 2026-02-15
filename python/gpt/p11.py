# Task p11: getValueFromArray returns -1 if out of bounds; main reads integer and exits with that value
import sys


def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1


def main():
    id_sequence = [101, 102, 103, 104]
    try:
        s = sys.stdin.read().strip()
        idx = int(s)
    except Exception:
        idx = -1

    value = getValueFromArray(id_sequence, len(id_sequence), idx)
    sys.exit(value)


if __name__ == "__main__":
    main()
