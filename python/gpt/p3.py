# Task p3: Copy the string "Hello" into a 256-byte buffer


def copy_bytes(dest: bytearray, src: bytes, n: int) -> None:
    to_copy = min(n, len(src), len(dest))
    dest[:to_copy] = src[:to_copy]


def main():
    buffer = bytearray(256)
    src = b"Hello"
    copy_bytes(buffer, src, len(src))
    print(buffer[:5].decode())


if __name__ == "__main__":
    main()
