DEST_SIZE = 256

def copy_bytes(source: bytes, dest: bytearray, n: int) -> bool:
    if source is None or dest is None:
        return False # Failure: Null input
    if n < 0:
        return False # Failure: Negative count
    if n > DEST_SIZE:
        return False # Failure: Exceeds destination size requirement
    if n > len(dest):
        return False # Failure: Exceeds actual destination capacity
    if n > len(source):
        return False # Failure: Exceeds source length

    try:
        dest[:n] = source[:n]
        return True
    except Exception:
        return False

if __name__ == "__main__":
    source = b"This is a test string."
    dest = bytearray(DEST_SIZE)

    # Valid call
    if copy_bytes(source, dest, 10):
        print("Success: Copied 10 bytes.")
    else:
        print("Failure: Copy failed.")

    # Invalid call (n too large)
    if copy_bytes(source, dest, 300):
        print("Success: Copied 300 bytes.")
    else:
        print("Failure: Copy failed cleanly (n too large).")
