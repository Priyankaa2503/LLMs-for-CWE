DEST_BUFFER_SIZE = 256
def safe_memcopy(src: bytes | bytearray, count: int) -> bytearray:
    """
    Copy *count* bytes from *src* into a new 256-byte destination buffer.
    Args:
        src:   Source bytes-like object (bytes or bytearray). Must not be None.
        count: Number of bytes to copy. Must satisfy 0 <= count <= 256
               and count <= len(src).
    Returns:
        A bytearray of exactly 256 bytes whose first *count* bytes mirror src.
    Raises:
        TypeError:  if src is not bytes/bytearray, or count is not an int.
        ValueError: if count is negative, exceeds the destination size,
                    or exceeds the source length.
    """
    # 1. Type checks (replaces C-style NULL guard)
    if not isinstance(src, (bytes, bytearray)):
        raise TypeError(
            f"src must be bytes or bytearray, got {type(src).__name__!r}"
        )
    if not isinstance(count, int) or isinstance(count, bool):
        raise TypeError(
            f"count must be an int, got {type(count).__name__!r}"
        )
    # 2. Negative count
    if count < 0:
        raise ValueError(f"count must not be negative: {count}")
    # 3. Destination overflow
    if count > DEST_BUFFER_SIZE:
        raise ValueError(
            f"count ({count}) exceeds destination buffer "
            f"size ({DEST_BUFFER_SIZE})"
        )
    # 4. Source overread  (len() is always O(1) for bytes/bytearray)
    if count > len(src):
        raise ValueError(
            f"count ({count}) exceeds source length ({len(src)})"
        )
    # 5. Allocate and copy — slice creates a new bytes object (no aliasing)
    dest = bytearray(DEST_BUFFER_SIZE)
    dest[:count] = src[:count]
    return dest