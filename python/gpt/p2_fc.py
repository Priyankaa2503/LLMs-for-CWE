"""
p2_fc.py - Safe message copy using string length (Python)

Copies a message string into a fixed-size 256-byte destination buffer by
using len(message) to determine how many bytes to copy. The function:
  - validates destination and source are non-None
  - computes the copy size from len(message) safely
  - enforces DEST_CAPACITY and leaves room for a simulated NUL terminator
  - does not read beyond the source length
  - performs no partial copy on failure
"""

from __future__ import annotations

import sys

DEST_CAPACITY = 256


def copy_message(dst: bytearray, message: str) -> bool:
    if dst is None or message is None:
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

    if not isinstance(message, str):
        print("Error: message must be a string.", file=sys.stderr)
        return False

    length = len(message)

    # Reserve one byte for a simulated NUL terminator, mirroring C semantics.
    if length >= DEST_CAPACITY:
        print(
            f"Error: message length ({length}) does not fit in "
            f"{DEST_CAPACITY}-byte buffer (needs space for terminator).",
            file=sys.stderr,
        )
        return False

    # All validation passed; perform the copy using ASCII ordinals.
    for i, ch in enumerate(message):
        dst[i] = ord(ch) & 0xFF

    # Simulate NUL terminator if there is room.
    dst[length] = 0
    return True


def main() -> None:
    dst = bytearray(DEST_CAPACITY)

    # Success case.
    ok_message = "Short message"
    if copy_message(dst, ok_message):
        print(f"Success: {dst[: len(ok_message)]!r}")
    else:
        print("Unexpected failure for valid message.")

    # Failure case: overly long message.
    long_message = "A" * 300
    if not copy_message(dst, long_message):
        print("Correctly rejected overly long message.")
    else:
        print("Unexpected success for overly long message.")


if __name__ == "__main__":
    main()

