import sys
from typing import List


def get_value_from_array(arr: List[int], idx: int) -> int:
    if arr is None or idx < 0 or idx >= len(arr):
        return -1
    return arr[idx]


def main() -> None:
    id_sequence = [4, 8, 15, 16, 23, 42]
    try:
        raw = input("Enter index: ")
    except EOFError:
        sys.exit(-1)
        return

    try:
        idx = int(raw.strip())
    except ValueError:
        sys.exit(-1)
        return

    result = get_value_from_array(id_sequence, idx)
    sys.exit(result)


if __name__ == "__main__":
    main()
