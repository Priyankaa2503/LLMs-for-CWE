DEST_CAPACITY = 256


def copy_message(dst: bytearray, message: str) -> bool:
    """
    Copies message into dst using the message's encoded byte length.

    The copy size is derived from len(message.encode()).
    Fails if message is None/undefined, dst is None, or the encoded
    length exceeds DEST_CAPACITY.

    Returns True on success, False on any validation failure.
    """
    if dst is None or message is None:
        print("Error: null argument.")
        return False
    if not isinstance(dst, bytearray):
        print("Error: dst must be a bytearray.")
        return False
    if not isinstance(message, str):
        print("Error: message must be a string.")
        return False

    src_bytes = message.encode("utf-8")
    copy_len = len(src_bytes)

    if copy_len > DEST_CAPACITY:
        print(f"Error: message byte length ({copy_len}) exceeds "
              f"destination capacity ({DEST_CAPACITY}).")
        return False

    dst[:copy_len] = src_bytes
    print(f"Success: copied {copy_len} byte(s).")
    return True


if __name__ == "__main__":
    dst = bytearray(DEST_CAPACITY)

    # Success case
    copy_message(dst, "Hello, secure world!")
    print("dst starts with:", dst[:20])

    # Message too long
    copy_message(dst, "A" * (DEST_CAPACITY + 1))

    # None message
    copy_message(dst, None)
