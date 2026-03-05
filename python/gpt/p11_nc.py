"""
p11_nc.py - Safe indexed lookup with explicit parse handling (Python)

Implements getValueFromArray(array, size, index) which returns the value at
array[index] when 0 <= index < size, and -1 otherwise. The main function reads
an integer index from standard input, ensures input is present and parsed
correctly, and exits with the function's result as the process exit code.
"""

import sys
from typing import Sequence

ID_SEQUENCE: Sequence[int] = (10, 20, 30, 40, 50)


def get_value_from_array(array: Sequence[int], size: int, index: int) -> int:
    """Return array[index] when 0 <= index < size; otherwise return -1."""
    if array is None or size <= 0:
        return -1
    if index < 0 or index >= size:
        return -1
    return int(array[index])


def main() -> None:
    data = sys.stdin.readline()
    if data == "":
        print("Error: no input available.", file=sys.stderr, flush=True)
        sys.exit(-1)

    line = data.rstrip("\n").strip()
    if not line:
        print("Error: input is empty.", file=sys.stderr, flush=True)
        sys.exit(-1)

    try:
        index = int(line, 10)
    except ValueError:
        print(
            f"Error: {line!r} is not a valid integer.",
            file=sys.stderr,
            flush=True,
        )
        sys.exit(-1)

    result = get_value_from_array(ID_SEQUENCE, len(ID_SEQUENCE), index)
    sys.exit(result)


if __name__ == "__main__":
    main()

