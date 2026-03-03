DEST_SIZE = 256
def safe_memcopy(src: bytes | bytearray, count: int) -> bytearray:
    """
    Copy *count* bytes from *src* into a new 256-byte destination buffer.
    Args:
        src:   Source data — must be bytes or bytearray (never None).
        count: Bytes to copy.  Must be an int satisfying
               0 <= count <= 256  and  count <= len(src).
    Returns:
        A bytearray of exactly 256 bytes whose first *count* bytes
        mirror *src*.  The remaining bytes are zero-initialised.
    Raises:
        TypeError:  src is not bytes/bytearray, or count is not an int.
        ValueError: count is negative, exceeds DEST_SIZE, or exceeds len(src).
    """
    # 1. Type-check src  (implicitly rejects None, lists, strings, …)
    if not isinstance(src, (bytes, bytearray)):
        raise TypeError(
            f"src must be bytes or bytearray, got {type(src).__name__!r}"
        )
    # 2. Type-check count
    #    bool is a subclass of int in Python, so exclude it explicitly —
    #    safe_memcopy(data, True) copying 1 byte would be a silent footgun.
    if not isinstance(count, int) or isinstance(count, bool):
        raise TypeError(
            f"count must be an int, got {type(count).__name__!r}"
        )
    # 3. Reject negative count
    if count < 0:
        raise ValueError(f"count must not be negative: {count}")
    # 4. Destination-overflow check
    if count > DEST_SIZE:
        raise ValueError(
            f"count ({count}) exceeds DEST_SIZE ({DEST_SIZE})"
        )
    # 5. Source over-read check  (len() is O(1) for bytes/bytearray)
    if count > len(src):
        raise ValueError(
            f"count ({count}) exceeds len(src) ({len(src)})"
        )
    # 6. All guards passed — allocate dest and copy via slice
    dest = bytearray(DEST_SIZE)   # zero-initialised
    dest[:count] = src[:count]    # slice never reads past the boundary
    return dest