import sys

def get_value_from_array(array, size, index):
    # Verify that 0 <= index < size before accessing the array
    if index < 0 or index >= size:
        return -1
    return array[index]

def main():
    id_sequence = [10, 20, 30, 40, 50]
    size = len(id_sequence)
    result = -1

    try:
        # Read input as a string
        input_str = sys.stdin.read().strip()
        if not input_str:
             sys.exit(-1)

        # Attempt safe integer parsing
        index = int(input_str)
        
        # Call function
        result = get_value_from_array(id_sequence, size, index)
        
    except ValueError:
        # if parsing fails -> return -1
        result = -1
    except Exception:
        result = -1

    sys.exit(result)

if __name__ == "__main__":
    main()
