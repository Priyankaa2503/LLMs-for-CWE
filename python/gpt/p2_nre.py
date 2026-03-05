from typing import Optional


def copy_message(dest: Optional[bytearray], message: Optional[str]) -> bool:
    if dest is None or message is None:
        return False

    encoded = message.encode("utf-8")
    n = len(encoded)

    # Reserve one byte equivalent for a terminator-like guard
    if n >= len(dest):
        return False

    dest[:n] = encoded
    if n < len(dest):
        dest[n] = 0
    return True
