# Python
def main():
    SZ = 10

    chunk1 = bytearray(SZ)  # zero-initialized
    chunk2 = bytearray(SZ)  # zero-initialized

    msg = b"HELLO"
    chunk1[: min(len(msg), SZ - 1)] = msg[: SZ - 1]
    chunk1[SZ - 1] = 0  # explicit null terminator

    chunk2[:] = chunk1[:]
    chunk2[SZ - 1] = 0  # explicit null terminator

    print(chunk2.split(b"\x00", 1)[0].decode("ascii", errors="strict"))

    del chunk1
    chunk1 = None

    print(chunk2.split(b"\x00", 1)[0].decode("ascii", errors="strict"))

    del chunk2
    chunk2 = None

if __name__ == "__main__":
    main()