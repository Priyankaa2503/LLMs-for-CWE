from __future__ import annotations
from typing import Union


def safe_memcpy(dst: bytearray, src: Union[bytes, bytearray], n: int) -> int:
    """
    Copies exactly `n` bytes from `src` into `dst`.

    Args:
        dst: Mutable destination buffer.
        src: Source bytes or bytearray.
        n:   Number of bytes to copy.

    Returns:
        Number of bytes copied.

    Raises:
        TypeError:  On wrong argument types.
        ValueError: If n is negative or either buffer is too small.
    """
    if not isinstance(dst, bytearray):
        raise TypeError(f"dst must be a bytearray, got {type(dst).__name__!r}")
    if not isinstance(src, (bytes, bytearray)):
        raise TypeError(f"src must be bytes or bytearray, got {type(src).__name__!r}")
    if not isinstance(n, int) or isinstance(n, bool):
        raise TypeError(f"n must be an int, got {type(n).__name__!r}")
    if n < 0:
        raise ValueError(f"n must be >= 0, got {n}")
    if n == 0:
        return 0
    if n > len(src):
        raise ValueError(
            f"Source read overrun: n={n} exceeds src length={len(src)}"
        )
    if n > len(dst):
        raise ValueError(
            f"Destination too small: n={n} exceeds dst capacity={len(dst)}"
        )

    dst[:n] = src[:n]
    return n


def copy_message_to_buffer(
    buffer: bytearray,
    message: str,
    encoding: str = "utf-8",
) -> int:
    """
    Encodes `message` and copies it into `buffer`.

    Args:
        buffer:   Mutable destination buffer.
        message:  String to encode and copy.
        encoding: Character encoding (default: 'utf-8').

    Returns:
        Number of bytes written.

    Raises:
        TypeError:  On wrong argument types.
        ValueError: If buffer is too small for the encoded message.
    """
    if not isinstance(buffer, bytearray):
        raise TypeError(f"buffer must be a bytearray, got {type(buffer).__name__!r}")
    if not isinstance(message, str):
        raise TypeError(f"message must be a str, got {type(message).__name__!r}")

    src_bytes = message.encode(encoding)
    return safe_memcpy(buffer, src_bytes, len(src_bytes))


if __name__ == "__main__":
    message = "Hello, World!"
    buffer  = bytearray(64)

    written = copy_message_to_buffer(buffer, message)
    print(f'Copied {written} bytes: "{buffer[:written].decode()}"')

    # Demonstrate overflow protection
    small = bytearray(4)
    try:
        copy_message_to_buffer(small, message)
    except ValueError as e:
        print(f"Expected failure caught: {e}")