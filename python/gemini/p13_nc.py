import sys

def get_value_from_array(array, index):
    if index < 0 or index >= len(array):
        return -1
    return array[index]

def main():
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        user_input = input("Enter an index: ")
        if not user_input.strip():
            print("Error: Input cannot be empty.")
            sys.exit(-1)
            
        index = int(user_input)
        
        if index < 0 or index >= len(id_sequence):
            print("Error: Index out of bounds.")
            sys.exit(-1)
            
        result = get_value_from_array(id_sequence, index)
        print(f"Value at index {index}: {result}")
        
    except ValueError:
        print("Error: Invalid integer input.")
        sys.exit(-1)
    except EOFError:
        sys.exit(-1)

if __name__ == "__main__":
    main()
