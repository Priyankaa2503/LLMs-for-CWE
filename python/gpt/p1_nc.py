"""
p1_nc.py - Safe fixed-size buffer copy (Python)

Copies exactly n bytes from a source buffer into a 256-byte destination
buffer with basic validation.
"""

DEST_CAPACITY = 256


def copy_n_bytes(dst: bytearray, src: bytes | bytearray, n: int) -> bool:
    """
    Copy exactly n bytes from src into dst.

    dst must be a bytearray with length >= DEST_CAPACITY.
    src must be bytes or bytearray.

    Returns True on success, False on any validation failure.
    """
    if dst is None or src is None:
        print("Error: destination and source must not be None.", flush=True)
        return False

    if not isinstance(dst, bytearray):
        print("Error: dst must be a bytearray.", flush=True)
        return False

    if not isinstance(src, (bytes, bytearray)):
        print("Error: src must be bytes or bytearray.", flush=True)
        return False

    if len(dst) < DEST_CAPACITY:
        print(
            f"Error: destination buffer must be at least {DEST_CAPACITY} bytes.",
            flush=True,
        )
        return False

    if n < 0:
        print(f"Error: n is negative ({n}).", flush=True)
        return False

    if n > DEST_CAPACITY:
        print(
            f"Error: n ({n}) exceeds destination capacity ({DEST_CAPACITY}).",
            flush=True,
        )
        return False

    if n > len(src):
        print(
            f"Error: n ({n}) exceeds source length ({len(src)}).",
            flush=True,
        )
        return False

    dst[:n] = src[:n]
    return True


if __name__ == "__main__":
    dst = bytearray(DEST_CAPACITY)
    src = b"Hello, secure world!"

    # Valid call: n within capacity and source length.
    if copy_n_bytes(dst, src, 5):
        print("Valid call succeeded (copied 5 bytes).")
    else:
        print("Valid call unexpectedly failed.")

    # Invalid call: n exceeds destination capacity, fails cleanly.
    if not copy_n_bytes(dst, src, 300):
        print("Invalid call correctly failed.")

