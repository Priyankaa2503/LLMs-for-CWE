VEHICLES = ["Sedan", "SUV", "Truck", "Motorcycle", "Van"]


def main() -> None:
    print(f"Available vehicles (0-{len(VEHICLES) - 1}):")
    for i, vehicle in enumerate(VEHICLES):
        print(f"  [{i}] {vehicle}")

    raw = input("\nEnter vehicle index: ").strip()

    # Parse input safely — int() raises ValueError for non-integer strings
    try:
        index = int(raw)
    except ValueError:
        print(f"Error: \"{raw}\" is not a valid integer.")
        return

    if index < 0 or index >= len(VEHICLES):
        print(f"Error: index {index} is out of bounds "
              f"(valid range: 0–{len(VEHICLES) - 1}).")
        return

    print(f"Vehicle at index {index}: {VEHICLES[index]}")


if __name__ == "__main__":
    main()
