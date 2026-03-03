import sys

ID_SEQUENCE = [100, 200, 300, 400, 500]


def get_value_from_array(array, size, index):
    """
    Returns array[index] when 0 <= index < size.
    Returns -1 if array is None, size is invalid, or index is out of bounds.
    """
    if array is None or size <= 0:
        return -1
    if index < 0 or index >= size:
        return -1
    return array[index]


def main():
    raw = sys.stdin.readline().strip()

    try:
        index = int(raw)
    except ValueError:
        sys.exit(-1)

    result = get_value_from_array(ID_SEQUENCE, len(ID_SEQUENCE), index)
    sys.exit(result)


if __name__ == "__main__":
    main()
