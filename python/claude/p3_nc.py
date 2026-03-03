DEST_CAPACITY = 256


def copy_string(src: str | None) -> bytearray | None:
    """
    Copies the string src into a fixed-size destination buffer using its
    computed byte length.  Appends a zero-byte null terminator.

    Returns a bytearray on success, None on any validation failure.
    """
    if src is None:
        print("Error: null source argument.")
        return None
    if not isinstance(src, str):
        print("Error: src must be a str.")
        return None

    src_bytes = src.encode("utf-8")
    n = len(src_bytes)

    # n + null terminator must fit within capacity
    if n >= DEST_CAPACITY:
        print(
            f"Error: source byte length ({n}) would overflow destination "
            f"capacity ({DEST_CAPACITY}) after null terminator."
        )
        return None

    dst = bytearray(DEST_CAPACITY)
    dst[:n] = src_bytes
    dst[n] = 0

    print(f'Success: copied "{src}" ({n} byte(s)).')
    return dst


if __name__ == "__main__":
    # Valid call
    result = copy_string("Hello")
    if result is not None:
        print("First 5 bytes copied successfully.")

    # Invalid: null source
    copy_string(None)
