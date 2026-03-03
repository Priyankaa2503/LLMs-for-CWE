import sys

ID_SEQUENCE = [10, 20, 30, 40, 50]


def get_value_from_array(array, size, index):
    """
    Returns array[index] when 0 <= index < size.
    Returns -1 for any invalid argument or out-of-bounds index.
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
