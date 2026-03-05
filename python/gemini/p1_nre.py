def copy_bytes(dest, source, n):
    """
    Copies n bytes from source to dest.
    dest: bytearray (assumed to be 256 bytes long based on prompt)
    source: bytes or bytearray
    n: int
    """
    DEST_SIZE = 256

    # Check that destination and source are valid
    if dest is None or source is None:
        return False # Fail

    # Confirm n is within bounds (0 to 256)
    if n > DEST_SIZE:
        return False # Fail
    
    # Also check against actual destination size if it differs
    if n > len(dest):
        return False # Fail

    if n < 0:
        return False # Fail

    # Avoid copying more bytes than the source actually contains
    if len(source) < n:
        return False # Fail

    # Otherwise copy exactly n bytes and report success
    # In Python, we can modify the mutable bytearray slice
    try:
        dest[:n] = source[:n]
        return True # Success
    except Exception:
        return False
