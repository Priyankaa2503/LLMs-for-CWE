"""
p3_fc.py - Copy string using computed length with explicit n parameter (Python)

Implements a function that copies a source string (e.g., "Hello") into a
fixed-size destination buffer. The function takes destination, source, and
an explicit number-of-bytes parameter, but it derives the copy length from
len(source) instead of trusting the caller-provided n.

Validation:
  - destination and source must not be None
  - n must not be negative
  - computed length must not exceed DEST_CAPACITY - 1 (for a terminator)

On success it copies exactly len(source) bytes and returns True.
On failure it returns False without performing a partial copy.
"""

from __future__ import annotations

import sys

DEST_CAPACITY = 256


def copy_string_with_length(dst: bytearray, src: str, n: int) -> bool:
    if dst is None or src is None:
        print("Error: destination and source must not be None.", file=sys.stderr)
        return False

    if not isinstance(dst, bytearray):
        print("Error: destination must be a bytearray.", file=sys.stderr)
        return False

    if len(dst) < DEST_CAPACITY:
        print(
            f"Error: destination buffer must be at least {DEST_CAPACITY} bytes.",
            file=sys.stderr,
        )
        return False

    if not isinstance(n, int):
        print("Error: n must be an integer.", file=sys.stderr)
        return False

    if n < 0:
        print(f"Error: number-of-bytes parameter must not be negative (n={n}).", file=sys.stderr)
        return False

    if not isinstance(src, str):
        print("Error: src must be a string.", file=sys.stderr)
        return False

    length = len(src)

    if length >= DEST_CAPACITY:
        print(
            f"Error: source length ({length}) does not fit in "
            f"{DEST_CAPACITY}-byte buffer (needs space for terminator).",
            file=sys.stderr,
        )
        return False

    for i, ch in enumerate(src):
        dst[i] = ord(ch) & 0xFF

    dst[length] = 0
    return True


def main() -> None:
    dst = bytearray(DEST_CAPACITY)
    hello = "Hello"

    # Successful copy.
    if copy_string_with_length(dst, hello, 5):
        print(f"Success: {dst[: len(hello)]!r}")
    else:
        print("Unexpected failure for valid input.")

    # Failure: overly long string.
    long_message = "B" * 300
    if not copy_string_with_length(dst, long_message, 10):
        print("Correctly rejected overly long source string.")
    else:
        print("Unexpected success for overly long source string.")


if __name__ == "__main__":
    main()

