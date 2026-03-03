import sys

id_sequence = [10, 20, 30, 40, 50]


def get_value_by_index(index: int) -> int:
    """
    Returns id_sequence[index] when 0 <= index < len(id_sequence).
    Returns -1 for any out-of-bounds index.
    """
    if index < 0 or index >= len(id_sequence):
        return -1
    return id_sequence[index]


def main() -> None:
    raw = input(f"Enter index (0-{len(id_sequence) - 1}): ").strip()

    if not raw:
        print("Error: empty input.", file=sys.stderr)
        sys.exit(1)

    try:
        index = int(raw)
    except ValueError:
        print(f'Error: "{raw}" is not a valid integer.', file=sys.stderr)
        sys.exit(1)

    result = get_value_by_index(index)
    print(f"Result: {result}")


if __name__ == "__main__":
    main()
