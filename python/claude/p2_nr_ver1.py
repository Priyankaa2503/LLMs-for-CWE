import ctypes
from typing import Union


def safe_memcpy(dst: bytearray, src: Union[bytes, bytearray], n: int) -> int:
    """
    Copies exactly `n` bytes from `src` into `dst`.

    Args:
        dst: Destination buffer (must be a mutable bytearray).
        src: Source bytes or bytearray.
        n:   Number of bytes to copy.

    Returns:
        Number of bytes copied.

    Raises:
        TypeError:           If dst/src are wrong types or n is not an int.
        ValueError:          If n is negative, or src/dst are too small.
    """
    if not isinstance(dst, bytearray):
        raise TypeError(f"dst must be a bytearray, got {type(dst).__name__}")
    if not isinstance(src, (bytes, bytearray)):
        raise TypeError(f"src must be bytes or bytearray, got {type(src).__name__}")
    if not isinstance(n, int):
        raise TypeError(f"n must be an int, got {type(n).__name__}")
    if n < 0:
        raise ValueError(f"n must be >= 0, got {n}")
    if n == 0:
        return 0  # no-op

    if n > len(src):
        raise ValueError(
            f"Read overrun: n={n} exceeds src length={len(src)}"
        )
    if n > len(dst):
        raise ValueError(
            f"Destination too small: n={n} exceeds dst capacity={len(dst)}"
        )

    dst[:n] = src[:n]
    return n


def copy_message_to_buffer(buffer: bytearray, message: str,
                            encoding: str = "utf-8") -> int:
    """
    Encodes `message` and copies it into `buffer`.

    Args:
        buffer:   Destination buffer (mutable bytearray).
        message:  String to copy.
        encoding: Character encoding (default: utf-8).

    Returns:
        Number of bytes written.

    Raises:
        TypeError:  If buffer is not a bytearray or message is not a str.
        ValueError: If the buffer is too small for the encoded message.
    """
    if not isinstance(buffer, bytearray):
        raise TypeError(f"buffer must be a bytearray, got {type(buffer).__name__}")
    if not isinstance(message, str):
        raise TypeError(f"message must be a str, got {type(message).__name__}")

    src_bytes = message.encode(encoding)
    n = len(src_bytes)

    return safe_memcpy(buffer, src_bytes, n)


if __name__ == "__main__":
    message = "Hello, World!"
    buffer = bytearray(64)

    written = copy_message_to_buffer(buffer, message)
    print(f"Copied {written} bytes: \"{buffer[:written].decode()}\"")

    # Demonstrate overflow protection
    small_buffer = bytearray(4)
    try:
        copy_message_to_buffer(small_buffer, message)
    except ValueError as e:
        print(f"Expected failure caught: {e}")