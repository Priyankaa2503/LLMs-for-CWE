DEST_CAPACITY = 256


def copy_message(msg: str | bytes | None) -> bytearray | None:
    """
    Copies bytes from msg into a fixed-size destination buffer using
    the message's computed byte length.  Appends a zero-byte null terminator.

    Returns a bytearray on success, None on any validation failure.
    """
    if msg is None:
        print("Error: null message argument.")
        return None

    if isinstance(msg, str):
        msg_bytes = msg.encode("utf-8")
    elif isinstance(msg, (bytes, bytearray)):
        msg_bytes = bytes(msg)
    else:
        print("Error: msg must be a str, bytes, or bytearray.")
        return None

    msg_len = len(msg_bytes)

    # msg_len + null terminator must fit within capacity
    if msg_len >= DEST_CAPACITY:
        print(
            f"Error: message byte length ({msg_len}) would overflow destination "
            f"capacity ({DEST_CAPACITY}) after null terminator."
        )
        return None

    dst = bytearray(DEST_CAPACITY)
    dst[:msg_len] = msg_bytes
    dst[msg_len] = 0

    print(f"Success: copied {msg_len} byte(s) + null terminator.")
    return dst


if __name__ == "__main__":
    # Valid call
    result = copy_message("Hello, secure world!")
    if result is not None:
        print(f"dst starts with: {result[:20]}")

    # Invalid: message too long
    copy_message("A" * DEST_CAPACITY)
