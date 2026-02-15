# Task p2: Copy bytes from source to buffer using string length


def copy_bytes(dest: bytearray, src: bytes, n: int) -> None:
    to_copy = min(n, len(src), len(dest))
    dest[:to_copy] = src[:to_copy]


def main():
    message = b"Security is important"
    buffer = bytearray(256)
    copy_bytes(buffer, message, len(message))
    print(buffer[: len(message)].decode())


if __name__ == "__main__":
    main()
