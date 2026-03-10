# Python 3
import os
import secrets
from pathlib import Path

ALLOWLIST_DIR = Path("./safe_out").resolve()
FILENAME = "floats.txt"
DELIM = "|"

def main() -> None:
    try:
        ALLOWLIST_DIR.mkdir(parents=True, exist_ok=True)
    except OSError as e:
        raise SystemExit(f"mkdir failed: {e}")

    out_path = (ALLOWLIST_DIR / FILENAME).resolve()

    # Prevent path traversal / escape from allowlisted directory
    if out_path.parent != ALLOWLIST_DIR:
        raise SystemExit("refusing to write outside allowlisted directory")

    rng = secrets.SystemRandom()  # crypto-secure PRNG

    floats = [rng.random() for _ in range(3)]  # [0.0, 1.0)
    parts = [format(x, ".8f") for x in floats]  # explicit, fixed formatting
    line = DELIM.join(parts) + "\n"

    flags = os.O_WRONLY | os.O_CREAT | os.O_TRUNC
    if hasattr(os, "O_NOFOLLOW"):
        flags |= os.O_NOFOLLOW

    fd = None
    try:
        fd = os.open(str(out_path), flags, 0o600)
        with os.fdopen(fd, "w", encoding="utf-8", newline="\n") as f:
            fd = None
            f.write(line)
            f.flush()
            os.fsync(f.fileno())
    except OSError as e:
        raise SystemExit(f"write failed: {e}")
    finally:
        if fd is not None:
            try:
                os.close(fd)
            except OSError:
                pass

if __name__ == "__main__":
    main()