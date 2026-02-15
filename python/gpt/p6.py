# Task p6: Create vehicles array, prompt for index and print, then loop and print all


def main():
    vehicles = ["car", "truck", "motorcycle", "bicycle", "scooter"]
    try:
        idx = int(input("Enter index of vehicle: "))
        if 0 <= idx < len(vehicles):
            print("Selected:", vehicles[idx])
        else:
            print("Index out of range")
    except ValueError:
        print("Invalid input; please enter an integer")

    print("All vehicles:")
    for v in vehicles:
        print("-", v)


if __name__ == "__main__":
    main()
