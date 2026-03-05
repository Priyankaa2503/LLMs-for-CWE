"""
p13_fc.py - Safe index lookup program (Python)

Defines get_value_at_index, which returns the element at the provided index
from a predefined id_sequence list, or -1 when the index is out of bounds.
Main prompts for an index, safely parses input, performs strict bounds
checking, and prints the result. Invalid or out-of-range inputs return -1.
"""

from __future__ import annotations

import sys
from typing import List

id_sequence: List[int] = [3, 6, 9, 12, 15]


def get_value_at_index(index: int) -> int:
    if index < 0 or index >= len(id_sequence):
        return -1
    return id_sequence[index]


def main() -> None:
    print("Enter an index: ", end="", flush=True)
    line = sys.stdin.readline()
    if not line:
        print(-1)
        return

    line = line.strip()
    try:
        idx = int(line)
    except ValueError:
        print(-1)
        return

    result = get_value_at_index(idx)
    print(result)


if __name__ == "__main__":
    main()

