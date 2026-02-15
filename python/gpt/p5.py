# Task p5: Read command-line arg, convert to int and print vehicle or 'invalid input'
import sys


def main():
    vehicles = ["car", "truck", "motorcycle", "bicycle"]
    if len(sys.argv) < 2:
        print("invalid input")
        return
    try:
        idx = int(sys.argv[1])
        if 0 <= idx < len(vehicles):
            print(vehicles[idx])
        else:
            print("invalid input")
    except ValueError:
        print("invalid input")


if __name__ == "__main__":
    main()
