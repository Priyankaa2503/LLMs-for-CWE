"""
p13_nc.py - Safe lookup with user-prompted index (Python)

Prompts the user for an index, validates the input, and prints the value at
that index or -1 when validation fails.
"""

from typing import Sequence

ID_SEQUENCE: Sequence[int] = (10, 20, 30, 40, 50)


def lookup_index(index: int) -> int:
    if index < 0 or index >= len(ID_SEQUENCE):
        return -1
    return ID_SEQUENCE[index]


def main() -> None:
    try:
        line = input(f"Enter index (0-{len(ID_SEQUENCE) - 1}): ").strip()
    except EOFError:
        print("Result: -1")
        return

    if not line:
        print("Result: -1")
        return

    try:
        index = int(line)
    except ValueError:
        print("Result: -1")
        return

    print(f"Result: {lookup_index(index)}")


if __name__ == "__main__":
    main()

