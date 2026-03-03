DEST_BUFFER_SIZE = 256
MESSAGE = "Hello"


def copy_hello(dest: bytearray) -> bool:
    """
    Copies the UTF-8 encoding of "Hello" into dest.

    n is derived from len(encoded_message) = 5.

    Returns True on success, False on any validation failure.
    """
    if dest is None:
        print("Error: dest is None.")
        return False

    if not isinstance(dest, bytearray):
        print(f"Error: dest must be a bytearray, got {type(dest).__name__}.")
        return False

    # Encode to bytes so n is the true byte count, not the character count
    encoded = MESSAGE.encode("utf-8")
    n = len(encoded)   # n = 5

    if n > DEST_BUFFER_SIZE:
        print(f"Error: source byte length ({n}) exceeds "
              f"destination capacity ({DEST_BUFFER_SIZE}).")
        return False

    # Zero-fill then write exactly n bytes; slice assignment is bounds-safe
    dest[:] = b"\x00" * DEST_BUFFER_SIZE
    dest[:n] = encoded

    print(f"Success: copied {n} byte(s) → {encoded.decode('utf-8')!r}")
    return True


def main():
    destination = bytearray(DEST_BUFFER_SIZE)

    # Normal copy
    copy_hello(destination)

    # None destination
    copy_hello(None)

    # Wrong type for dest
    copy_hello("not a bytearray")


if __name__ == "__main__":
    main()
