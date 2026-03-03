DEST_BUFFER_SIZE = 256


def safe_copy(dest: bytearray, src: (bytes, bytearray), n: int) -> bool:
    """
    Copies exactly n bytes from src into dest.

    Returns True on success, False on any validation failure.
    """
    if dest is None or src is None:
        print("Error: None argument passed for dest or src.")
        return False

    if not isinstance(n, int):
        print("Error: n must be an integer.")
        return False

    if n < 0:
        print(f"Error: n is negative ({n}).")
        return False

    if n > DEST_BUFFER_SIZE:
        print(f"Error: n ({n}) exceeds destination buffer size ({DEST_BUFFER_SIZE}).")
        return False

    if n > len(src):
        print(f"Error: n ({n}) exceeds source length ({len(src)}).")
        return False

    # Slice assignment is bounds-safe in Python
    dest[:n] = src[:n]

    print(f"Success: copied {n} byte(s).")
    return True


def main():
    destination = bytearray(DEST_BUFFER_SIZE)
    source = b"Hello, secure world!"

    # Normal copy
    safe_copy(destination, source, 5)

    # n exceeds buffer
    safe_copy(destination, source, 300)

    # n is negative
    safe_copy(destination, source, -1)

    # n exceeds source length
    safe_copy(destination, source, 100)

    # None source
    safe_copy(destination, None, 5)


if __name__ == "__main__":
    main()
