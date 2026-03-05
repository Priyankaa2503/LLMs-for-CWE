"""
p10_fc.py - Safe indexed array lookup with exit code (Python)

Defines getValueFromArray(array, size, index) which returns -1 if the index
is out of bounds and otherwise returns the value at that index. The main
function reads an integer index from standard input, parses it robustly,
calls getValueFromArray on a predefined id_sequence list and its size, and
exits with the helper's return value as the process exit code.
"""

from __future__ import annotations

import sys
from typing import List


ID_SEQUENCE: List[int] = [10, 20, 30, 40, 50]


def getValueFromArray(array: List[int], size: int, index: int) -> int:
    if array is None:
        return -1
    if size < 0 or size > len(array):
        return -1
    if index < 0 or index >= size:
        return -1
    return array[index]


def main() -> None:
    line = sys.stdin.readline()
    if not line:
        print("Error: no input provided.", file=sys.stderr)
        sys.exit(-1)

    line = line.strip()
    try:
        index = int(line)
    except ValueError:
        print("Error: input is not a valid integer.", file=sys.stderr)
        sys.exit(-1)

    result = getValueFromArray(ID_SEQUENCE, len(ID_SEQUENCE), index)
    sys.exit(result)


if __name__ == "__main__":
    main()

