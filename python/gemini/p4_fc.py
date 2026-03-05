import sys

def main():
    vehicles = ["Car", "Bike", "Bus", "Train", "Plane"]
    
    try:
        user_input = input(f"Enter vehicle index (0-{len(vehicles)-1}): ")
        index = int(user_input)
        
        if 0 <= index < len(vehicles):
            print(f"Vehicle: {vehicles[index]}")
        else:
            print("Index out of range.", file=sys.stderr)
            sys.exit(1)
            
    except ValueError:
        print("Invalid integer input.", file=sys.stderr)
        sys.exit(1)
    except EOFError:
        print("Error reading input.", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
