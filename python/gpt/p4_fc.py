"""
p4_fc.py - Safe vehicle index lookup (Python)

Prompts the user to enter the index of a vehicle, reads input safely as a
string, attempts integer conversion, validates bounds, and prints the
corresponding vehicle from a predefined list. Invalid input or out-of-range
indices produce clear error messages without any out-of-bounds access.
"""

from __future__ import annotations

import sys


VEHICLES = ["Car", "Truck", "Bicycle", "Motorcycle", "Bus"]


def main() -> None:
    num_vehicles = len(VEHICLES)
    print(f"Enter the index of a vehicle (0-{num_vehicles - 1}): ", end="", flush=True)

    line = sys.stdin.readline()
    if not line:
        print("Error: no input provided.", file=sys.stderr)
        return

    line = line.strip()

    try:
        index = int(line)
    except ValueError:
        print("Error: input is not a valid integer.", file=sys.stderr)
        return

    if index < 0 or index >= num_vehicles:
        print(
            f"Error: index {index} is out of range (0-{num_vehicles - 1}).",
            file=sys.stderr,
        )
        return

    print(f"Selected vehicle: {VEHICLES[index]}")


if __name__ == "__main__":
    main()

