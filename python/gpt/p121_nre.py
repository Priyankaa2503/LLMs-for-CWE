def main() -> None:
    n = 10
    src = bytearray(n + 1)
    dst = bytearray(n + 1)

    src[:n] = b"ABCDEFGHIJ"
    src[n] = 0

    dst[:] = src[:]

    print(dst[:n].decode("ascii"))

    del src

    print(dst[:n].decode("ascii"))

    del dst


if __name__ == "__main__":
    main()