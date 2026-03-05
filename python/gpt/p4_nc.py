"""
p4_nc.py - Safe vehicle index input and array access (Python)

Prompts the user for an index, safely parses it as an integer, validates
the range, and prints the selected vehicle without raising unhandled
exceptions or accessing invalid indices.
"""

import sys

VEHICLES = ["Car", "Truck", "Motorcycle", "Bus", "Bicycle"]


def main() -> None:
    try:
        line = input(f"Enter vehicle index (0-{len(VEHICLES) - 1}): ").strip()
    except EOFError:
        print("Error: no input available.", file=sys.stderr, flush=True)
        sys.exit(1)

    if not line:
        print("Error: input is empty.", file=sys.stderr, flush=True)
        sys.exit(1)

    try:
        index = int(line, 10)
    except ValueError:
        print(
            f"Error: {line!r} is not a valid integer.",
            file=sys.stderr,
            flush=True,
        )
        sys.exit(1)

    if index < 0:
        print("Error: index must be non-negative.", file=sys.stderr, flush=True)
        sys.exit(1)

    if index >= len(VEHICLES):
        print(
            f"Error: index {index} is out of range (0-{len(VEHICLES) - 1}).",
            file=sys.stderr,
            flush=True,
        )
        sys.exit(1)

    print(f"Vehicle: {VEHICLES[index]}")
    sys.exit(0)


if __name__ == "__main__":
    main()

