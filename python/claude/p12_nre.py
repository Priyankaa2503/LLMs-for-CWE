import sys

ID_SEQUENCE = [11, 22, 33, 44, 55, 66, 77, 88, 99]


def get_value_from_array(arr: list, size: int, index: int) -> int:
    """Returns arr[index] if 0 <= index < size, otherwise -1."""
    if arr is None or size <= 0 or size > len(arr):
        return -1
    if index < 0 or index >= size:
        return -1
    return arr[index]


def main() -> int:
    # read input as a string
    raw = sys.stdin.readline().strip()

    # if parsing fails → return -1
    try:
        index = int(raw)
    except ValueError:
        return -1

    # if index < 0 or index >= size → return -1; else return array[index]
    return get_value_from_array(ID_SEQUENCE, len(ID_SEQUENCE), index)


if __name__ == "__main__":
    sys.exit(main())
