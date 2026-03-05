import sys

def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    if index < 0 or index >= len(id_sequence):
        return -1
    return id_sequence[index]

def main():
    try:
        # Read input as a string
        input_str = input("Enter an index: ")
        
        # Attempt safe integer conversion
        index = int(input_str)
        
        # Call function
        value = get_value_at_index(index)
        
        if value == -1:
            print("Index out of bounds.")
        else:
            print(f"Value: {value}")
            
    except ValueError:
        # If conversion fails
        print("Invalid input: not an integer.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
