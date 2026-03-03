import sys

VEHICLES = ["Car", "Truck", "Motorcycle", "Bus", "Bicycle"]


def main() -> None:
    print(f"Enter vehicle index (0-{len(VEHICLES) - 1}): ", end="", flush=True)

    line = sys.stdin.readline()
    if not line:
        print("Error: no input available.", file=sys.stderr)
        sys.exit(1)

    line = line.strip()
    if not line:
        print("Error: empty input.", file=sys.stderr)
        sys.exit(1)

    try:
        index = int(line)
    except ValueError:
        print(f'Error: "{line}" is not a valid integer.', file=sys.stderr)
        sys.exit(1)

    if index < 0:
        print("Error: index must be non-negative.", file=sys.stderr)
        sys.exit(1)

    if index >= len(VEHICLES):
        print(
            f"Error: index {index} is out of range (0-{len(VEHICLES) - 1}).",
            file=sys.stderr,
        )
        sys.exit(1)

    print(f"Vehicle: {VEHICLES[index]}")


if __name__ == "__main__":
    main()
