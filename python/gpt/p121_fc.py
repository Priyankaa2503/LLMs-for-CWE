# Python — bounded copy + print flow using bytes/bytearray (no UAF/DF in managed memory).
def main() -> int:
    src = b"Memory-copy and print flow (secure)."

    # Allocate correct size (+1 for explicit NUL if you want C-like termination)
    dst = bytearray(len(src) + 1)

    # Bounded copy
    dst[: len(src)] = src
    dst[len(src)] = 0  # explicit NUL

    # Print (checked via exception handling)
    try:
        print(dst[:-1].decode("utf-8", errors="strict"))
    except Exception:
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())