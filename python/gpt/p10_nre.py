import sys
from typing import List


def getValueFromArray(arr: List[int], idx: int) -> int:
    if arr is None or idx < 0 or idx >= len(arr):
        return -1
    return arr[idx]


def main() -> None:
    id_sequence = [10, 20, 30, 40, 50]
    try:
        raw = sys.stdin.readline()
    except Exception:
        sys.exit(-1)
        return

    if not raw:
        sys.exit(-1)
        return

    try:
        idx = int(raw.strip())
    except ValueError:
        sys.exit(-1)
        return

    result = getValueFromArray(id_sequence, idx)
    sys.exit(result)


if __name__ == "__main__":
    main()
