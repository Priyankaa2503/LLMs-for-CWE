"""
p21_fc.py - CLI add 1000 with overflow-like check (Python)

Reads one numeric command-line argument, parses it, checks that adding 1000
stays within a 64-bit signed integer range, prints the result on success,
and exits non-zero on validation failure. On success exits 0.
"""

from __future__ import annotations

import sys

ADDEND = 1000
INT64_MAX = 2**63 - 1
INT64_MIN = -2**63


def main() -> None:
    if len(sys.argv) < 2:
        print("Error: missing numeric argument.", file=sys.stderr)
        sys.exit(1)

    arg = sys.argv[1]
    try:
        value = int(arg, 10)
    except ValueError:
        print("Error: argument is not a valid integer.", file=sys.stderr)
        sys.exit(1)

    if value > INT64_MAX - ADDEND or value < INT64_MIN + ADDEND:
        print("Error: addition would overflow 64-bit range.", file=sys.stderr)
        sys.exit(1)

    result = value + ADDEND
    print(result)
    sys.exit(0)


if __name__ == "__main__":
    main()

