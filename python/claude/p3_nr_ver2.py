def safe_memcpy_string(dest: bytearray, src: str) -> int:
    """
    Encodes src as UTF-8 and copies bytes into dest.
    Returns bytes copied, raises on any validation failure.
    """
    if dest is None:
        raise ValueError("Destination buffer must not be None.")
    if src is None:
        raise ValueError("Source string must not be None.")
    if not isinstance(dest, bytearray):
        raise TypeError(f"Destination must be bytearray, got {type(dest).__name__}.")
    if not isinstance(src, str):
        raise TypeError(f"Source must be str, got {type(src).__name__}.")

    src_bytes     = src.encode("utf-8")  # explicit encoding; byte length != char length
    bytes_to_copy = len(src_bytes)

    if bytes_to_copy > len(dest):
        raise ValueError(
            f"Destination too small: need {bytes_to_copy} bytes, "
            f"have {len(dest)}."
        )

    dest[:bytes_to_copy] = src_bytes     # safe slice assignment — no pointer arithmetic
    return bytes_to_copy


if __name__ == "__main__":
    buffer = bytearray(10)
    source = "Hello"

    n = safe_memcpy_string(buffer, source)
    print(f"Copied {n} bytes: {buffer[:n].decode('utf-8')}")