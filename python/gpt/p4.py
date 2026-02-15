# Task p4: Prompt user for vehicle index and print vehicle


def main():
    vehicles = ["car", "truck", "motorcycle", "bicycle", "scooter"]
    idx = input("Enter index of vehicle: ")
    try:
        i = int(idx)
        if 0 <= i < len(vehicles):
            print("Selected vehicle:", vehicles[i])
        else:
            print("Index out of range")
    except ValueError:
        print("Invalid input; please enter an integer")


if __name__ == "__main__":
    main()
