import sys

VEHICLES = ["Car", "Truck", "Motorcycle", "Bus", "Bicycle"]

def main():
    num_vehicles = len(VEHICLES)
    raw = input(f"Enter vehicle index (0-{num_vehicles - 1}): ").strip()

    try:
        index = int(raw)
    except ValueError:
        print(f'Error: "{raw}" is not a valid integer.', file=sys.stderr)
        sys.exit(1)

    if index < 0 or index >= num_vehicles:
        print(f"Error: index {index} is out of range (0-{num_vehicles - 1}).",
              file=sys.stderr)
        sys.exit(1)

    print(f"Vehicle: {VEHICLES[index]}")


if __name__ == "__main__":
    main()
