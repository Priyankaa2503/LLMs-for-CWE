import sys

ID_SEQUENCE = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]


def get_value_from_array(arr: list, size: int, index: int) -> int:
    """
    Returns the element at index in arr, or -1 if the index is out of bounds
    or the array / size arguments are invalid.
    """
    if arr is None or size <= 0 or size > len(arr):
        print("Error: invalid array or size.", file=sys.stderr)
        return -1

    if index < 0 or index >= size:
        print(f"Error: index {index} is out of bounds "
              f"(valid range: 0–{size - 1}).", file=sys.stderr)
        return -1

    return arr[index]


def main() -> int:
    size = len(ID_SEQUENCE)
    print(f"ID_SEQUENCE has {size} elements (indices 0–{size - 1}).")

    raw = input("Enter an index: ").strip()

    # int() raises ValueError for non-integer strings (floats, text, empty)
    try:
        index = int(raw)
    except ValueError:
        print(f"Error: \"{raw}\" is not a valid integer.", file=sys.stderr)
        return -1

    result = get_value_from_array(ID_SEQUENCE, size, index)
    print(f"Result: {result}")
    return result


if __name__ == "__main__":
    sys.exit(main())
