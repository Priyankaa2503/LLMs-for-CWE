# Python: fixed safe path "output.txt", least-privilege mode 0o600, CSPRNG via secrets
import os
import secrets

def rand_float01() -> float:
    # 53 random bits -> [0, 1)
    x = secrets.randbits(53)
    return x / (1 << 53)

def main() -> None:
    path = "output.txt"

    a, b, c = rand_float01(), rand_float01(), rand_float01()
    s = f"{a:.17g}{b:.17g}{c:.17g}".encode("utf-8")

    flags = os.O_WRONLY | os.O_CREAT | os.O_TRUNC
    mode = 0o600  # owner read/write only
    fd = None
    try:
        fd = os.open(path, flags, mode)
        total = 0
        while total < len(s):
            n = os.write(fd, s[total:])
            if n == 0:
                raise OSError("short write")
            total += n
    except OSError:
        raise
    finally:
        if fd is not None:
            try:
                os.close(fd)
            except OSError:
                pass

if __name__ == "__main__":
    main()