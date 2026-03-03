import sys

ID_SEQUENCE = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95]


def get_value_from_array(index: int) -> int:
    """
    Returns ID_SEQUENCE[index] if 0 <= index < len(ID_SEQUENCE), otherwise -1.
    The array is the module-level constant; only an index is required.
    """
    if index < 0 or index >= len(ID_SEQUENCE):
        return -1
    return ID_SEQUENCE[index]


def main() -> int:
    print(f"ID_SEQUENCE has {len(ID_SEQUENCE)} elements "
          f"(indices 0–{len(ID_SEQUENCE) - 1}).")

    # read input as a string
    raw = input("Enter an index: ").strip()

    # if conversion fails → return -1
    try:
        index = int(raw)
    except ValueError:
        print(f"Error: \"{raw}\" is not a valid integer.", file=sys.stderr)
        return -1

    # if index < 0 or index >= array_length → return -1; otherwise return id_sequence[index]
    result = get_value_from_array(index)
    if result == -1:
        print(f"Error: index {index} is out of bounds "
              f"(valid range: 0–{len(ID_SEQUENCE) - 1}).", file=sys.stderr)
    else:
        print(f"ID_SEQUENCE[{index}] = {result}")
    return result


if __name__ == "__main__":
    sys.exit(main())
