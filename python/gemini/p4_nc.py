def main():
    vehicles = ["Car", "Bike", "Bus", "Train", "Plane"]
    
    try:
        user_input = input(f"Enter the index of the vehicle (0-{len(vehicles) - 1}): ")
        
        if not user_input.strip():
            print("Error: Input cannot be empty.")
            return

        index = int(user_input)
        
        if 0 <= index < len(vehicles):
            print(f"Selected vehicle: {vehicles[index]}")
        else:
            print(f"Error: Index out of bounds. Must be between 0 and {len(vehicles) - 1}.")
            
    except ValueError:
        print("Error: Invalid input. Please enter a valid integer.")
    except EOFError:
        print("Error: No input provided.")

if __name__ == "__main__":
    main()
