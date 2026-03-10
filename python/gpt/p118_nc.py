# Python: generate 3 random floats, stringify, concatenate, write to a fixed file with 0600 perms.
import os
import random

def main() -> int:
    path = "./random_floats.txt"  # fixed, not user-controlled

    a = random.random()
    b = random.random()
    c = random.random()

    out = f"{a:.9f}{b:.9f}{c:.9f}"

    flags = os.O_WRONLY | os.O_CREAT | os.O_TRUNC
    mode = 0o600  # least-privilege where applicable (POSIX)
    try:
        fd = os.open(path, flags, mode)
        try:
            with os.fdopen(fd, "w", encoding="utf-8", newline="") as f:
                f.write(out)
                f.flush()
                os.fsync(f.fileno())
        except OSError:
            try:
                os.close(fd)
            except OSError:
                pass
            raise
    except OSError as e:
        raise SystemExit(f"Write failed: {e}") from e

    return 0

if __name__ == "__main__":
    raise SystemExit(main())