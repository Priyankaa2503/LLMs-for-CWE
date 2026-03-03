DEST_CAPACITY = 256


def safe_copy(dst: bytearray, src: bytes | bytearray, n: int) -> bool:
    """
    Copies exactly n bytes from src into dst.

    dst must be a bytearray of length >= DEST_CAPACITY.
    src must be bytes or bytearray.
    Returns True on success, False on any validation failure.
    """
    if dst is None or src is None:
        print("Error: null argument.", flush=True)
        return False
    if not isinstance(dst, bytearray):
        print("Error: dst must be a bytearray.")
        return False
    if not isinstance(src, (bytes, bytearray)):
        print("Error: src must be bytes or bytearray.")
        return False
    if n < 0:
        print(f"Error: n is negative ({n}).")
        return False
    if n > DEST_CAPACITY:
        print(f"Error: n ({n}) exceeds destination capacity ({DEST_CAPACITY}).")
        return False
    if n > len(src):
        print(f"Error: n ({n}) exceeds source length ({len(src)}).")
        return False

    dst[:n] = src[:n]
    print(f"Success: copied {n} byte(s).")
    return True


if __name__ == "__main__":
    dst = bytearray(DEST_CAPACITY)
    src = b"Hello, secure world!"

    # Valid call
    safe_copy(dst, src, 5)

    # Invalid: n exceeds destination capacity
    safe_copy(dst, src, 300)
