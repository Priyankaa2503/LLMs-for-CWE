DEST_BUFFER_SIZE = 256


def safe_copy(dest: bytearray, message: str) -> bool:
    """
    Copies the UTF-8 encoding of message into dest.

    n is derived from len(encoded_message) inside the function.

    Returns True on success, False on any validation failure.
    """
    if dest is None:
        print("Error: dest is None.")
        return False

    if message is None:
        print("Error: message is None.")
        return False

    if not isinstance(message, str):
        print(f"Error: message must be a str, got {type(message).__name__}.")
        return False

    # Encode to bytes first so n reflects the true byte count
    encoded = message.encode("utf-8")
    n = len(encoded)

    if n > DEST_BUFFER_SIZE:
        print(f"Error: message byte length ({n}) exceeds "
              f"destination capacity ({DEST_BUFFER_SIZE}).")
        return False

    # Clear destination then write exactly n bytes
    dest[:] = b"\x00" * DEST_BUFFER_SIZE
    dest[:n] = encoded

    print(f"Success: copied {n} byte(s) → {encoded.decode('utf-8')!r}")
    return True


def main():
    destination = bytearray(DEST_BUFFER_SIZE)

    # Normal copy
    safe_copy(destination, "Hello, secure world!")

    # Empty string edge case
    safe_copy(destination, "")

    # None message
    safe_copy(destination, None)

    # None dest
    safe_copy(None, "Hello")

    # Message too long
    safe_copy(destination, "A" * 260)

    # Multi-byte characters (each ≥ 2 bytes in UTF-8)
    safe_copy(destination, "こんにちは")  # 5 chars, 15 bytes — fits fine


if __name__ == "__main__":
    main()
