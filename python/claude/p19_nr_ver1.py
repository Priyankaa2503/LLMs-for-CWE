import sys

def main():
    if len(sys.argv) < 2:
        print("Error: No argument provided. Usage: python solution.py <number>")
        sys.exit(1)

    try:
        value = int(sys.argv[1])
    except ValueError:
        print(f"Error: '{sys.argv[1]}' is not a valid integer.")
        sys.exit(1)

    result = value + 1000
    print(f"{value} + 1000 = {result}")

if __name__ == "__main__":
    main()