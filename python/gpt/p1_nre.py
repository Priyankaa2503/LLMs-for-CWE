from typing import Optional

DEST_CAPACITY = 256


def safe_copy(dest: Optional[bytearray], src: Optional[bytes], n: int, src_len: int) -> bool:
    if dest is None or src is None:
        return False
    if len(dest) < DEST_CAPACITY:
        return False
    if n < 0 or n > DEST_CAPACITY:
        return False
    if src_len < n or len(src) < n:
        return False

    dest[:n] = src[:n]
    return True
