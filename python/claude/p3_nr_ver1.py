def safe_memcpy_string(dest: bytearray, src: str) -> int:
    """
    Copies src (encoded as UTF-8) into dest bytearray.
    Returns number of bytes copied, or raises on validation failure.
    """
    if dest is None:
        raise ValueError("Destination buffer must not be None.")
    if src is None:
        raise ValueError("Source string must not be None.")
    if not isinstance(dest, bytearray):
        raise TypeError("Destination must be a bytearray.")
    if not isinstance(src, str):
        raise TypeError("Source must be a str.")

    src_bytes = src.encode("utf-8")       # safe, explicit encoding
    bytes_to_copy = len(src_bytes)

    if bytes_to_copy > len(dest):
        raise ValueError(
            f"Destination too small: need {bytes_to_copy} bytes, "
            f"have {len(dest)}."
        )

    dest[:bytes_to_copy] = src_bytes      # slice assignment = memcpy
    return bytes_to_copy


if __name__ == "__main__":
    buffer = bytearray(10)
    source = "Hello"

    n = safe_memcpy_string(buffer, source)
    print(f"Copied {n} bytes: {buffer[:n].decode('utf-8')}")