MESSAGE = b"Hello"


def copy_hello(dest: bytearray) -> bool:
    if dest is None:
        return False

    n = len(MESSAGE)
    if n + 1 > len(dest):
        return False

    dest[:n] = MESSAGE
    dest[n] = 0
    return True
