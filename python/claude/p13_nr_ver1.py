id_sequence = [10, 20, 30, 40, 50]

def get_value(index):
    if not isinstance(index, int) or index < 0 or index >= len(id_sequence):
        return -1
    return id_sequence[index]

def main():
    try:
        index = int(input("Enter an index: "))
    except ValueError:
        print("Invalid input.")
        return
    print(f"Result: {get_value(index)}")

main()