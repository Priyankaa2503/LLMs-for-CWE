DEST_CAPACITY = 256


def copy_string(dst: bytearray, src: str, n: int) -> bool:
    """
    Copies exactly n bytes from src into dst.
    n must be derived from len(src.encode()) by the caller.

    Returns True on success, False on any validation failure.
    """
    if dst is None or src is None:
        print("Error: null argument.")
        return False
    if not isinstance(dst, bytearray):
        print("Error: dst must be a bytearray.")
        return False
    if not isinstance(src, str):
        print("Error: src must be a string.")
        return False
    if n < 0:
        print(f"Error: n is negative ({n}).")
        return False
    if n > DEST_CAPACITY:
        print(f"Error: n ({n}) exceeds destination capacity ({DEST_CAPACITY}).")
        return False

    src_bytes = src.encode("utf-8")
    if n != len(src_bytes):
        print(f"Error: n ({n}) does not match source byte length ({len(src_bytes)}).")
        return False

    dst[:n] = src_bytes
    print(f'Success: copied "{src}" ({n} byte(s)).')
    return True


if __name__ == "__main__":
    dst = bytearray(DEST_CAPACITY)
    src = "Hello"
    n = len(src.encode("utf-8"))   # derive n from string length

    # Success case
    copy_string(dst, src, n)

    # Mismatched n
    copy_string(dst, src, n + 3)

    # None source
    copy_string(dst, None, n)
