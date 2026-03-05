def main() -> None:
    vehicles = ["Car", "Bike", "Truck", "Bus"]

    try:
        raw = input("Enter vehicle index: ")
    except EOFError:
        print("No input provided")
        return

    try:
        idx = int(raw.strip())
    except ValueError:
        print("Invalid index")
        return

    if idx < 0 or idx >= len(vehicles):
        print("Index out of range")
        return

    print(f"Vehicle: {vehicles[idx]}")


if __name__ == "__main__":
    main()
