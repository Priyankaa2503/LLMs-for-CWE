"""
p1_fc.py - Safe fixed-size byte copy (Python)

Copies exactly n bytes from a source bytes-like object into a 256-byte
destination buffer with strict validation:
  - dst and src must be non-None
  - dst must be a bytearray of length at least DEST_CAPACITY
  - n must be an integer, non-negative, and <= DEST_CAPACITY
  - src must contain at least n bytes

On success the function copies exactly n bytes and returns True.
On validation failure it returns False and performs no partial copy.
"""

from __future__ import annotations

from typing import ByteString
import sys

DEST_CAPACITY = 256


def copy_n_bytes(dst: bytearray, src: ByteString, n: int) -> bool:
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
        print(f"Error: n is negative ({n}).", file=sys.stderr)
        return False

    if n > DEST_CAPACITY:
        print(
            f"Error: n ({n}) exceeds destination capacity ({DEST_CAPACITY}).",
            file=sys.stderr,
        )
        return False

    if n > len(src):
        print(
            f"Error: n ({n}) exceeds source length ({len(src)}).",
            file=sys.stderr,
        )
        return False

    dst[:n] = src[:n]
    return True


def main() -> None:
    dst = bytearray(DEST_CAPACITY)
    src = b"Hello, secure world!"

    # Valid call.
    if copy_n_bytes(dst, src, 5):
        print(f"Valid call succeeded (copied 5 bytes): {dst[:5]!r}")
    else:
        print("Valid call unexpectedly failed.")

    # Invalid call.
    if not copy_n_bytes(dst, src, 300):
        print("Invalid call correctly failed.")


if __name__ == "__main__":
    main()

