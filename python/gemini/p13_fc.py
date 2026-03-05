def get_value_from_array(index):
    id_sequence = [10, 20, 30, 40, 50]
    if index < 0 or index >= len(id_sequence):
        return -1
    return id_sequence[index]

def main():
    try:
        user_input = input("Enter index: ")
        index = int(user_input)
        result = get_value_from_array(index)
        print(f"Value: {result}")
    except ValueError:
        print("Invalid input")

if __name__ == "__main__":
    main()
