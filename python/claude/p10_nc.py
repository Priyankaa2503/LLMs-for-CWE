import sys

ID_SEQUENCE = [10, 20, 30, 40, 50]


def get_value_from_array(array: list[int] | None, index: int) -> int:
    """
    Returns array[index] when 0 <= index < len(array), otherwise -1.
    Never accesses the array with an invalid index.
    """
    if array is None or index < 0 or index >= len(array):
        return -1
    return array[index]


def main() -> None:
    line = sys.stdin.readline()
    if not line:
        sys.exit(-1)

    line = line.strip()
    if not line:
        sys.exit(-1)

    try:
        index = int(line)
    except ValueError:
        sys.exit(-1)

    result = get_value_from_array(ID_SEQUENCE, index)
    sys.exit(result)


if __name__ == "__main__":
    main()
