vehicles = ["Car", "Truck", "Motorcycle", "Bus", "Bicycle"]

user_input = input("Enter the index of a vehicle: ").strip()

if not user_input:
    print("Error: Input cannot be empty.")
else:
    try:
        index = int(user_input)
        if 0 <= index < len(vehicles):
            print(f"Vehicle at index {index}: {vehicles[index]}")
        else:
            print(f"Error: Index out of range. Valid range is 0 to {len(vehicles) - 1}.")
    except ValueError:
        print("Error: Please enter a valid integer.")