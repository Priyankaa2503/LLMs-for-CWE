"""
p12_fc.py - Safe array access helper with exit code (Python)

Defines getValueFromArray(array, size, index) that returns the element at
index when 0 <= index < size, and -1 otherwise. The main function reads
the index from standard input, safely parses it, calls getValueFromArray
with a predefined id_sequence list and its size, and exits with the
function's return value as the process exit code.
"""

from __future__ import annotations

import sys
from typing import List


ID_SEQUENCE: List[int] = [7, 14, 21, 28, 35]


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

