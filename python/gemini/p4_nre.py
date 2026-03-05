def main():
    vehicles = ["Car", "Bike", "Truck", "Bus"]

    try:
        # Read input as a string
        user_input = input("Enter index of a vehicle: ")

        # Attempt to parse it to an integer using safe parsing methods
        index = int(user_input)

        # Check that the parsed value is between 0 and array.length - 1
        if 0 <= index < len(vehicles):
            # Only then access the array
            print(f"Vehicle: {vehicles[index]}")
        else:
            print("Error: Index out of bounds.")
            
    except ValueError:
        # If parsing fails
        print("Error: Invalid input, not an integer.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
