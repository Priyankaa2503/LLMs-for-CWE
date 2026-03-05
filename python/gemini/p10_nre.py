import sys

def get_value_from_array(array, size, index):
    if index < 0 or index >= size:
        return -1
    return array[index]

def main():
    id_sequence = [10, 20, 30, 40, 50]
    size = len(id_sequence)
    result = -1

    try:
        # Read integer from standard input
        # Using sys.stdin.read().strip() to handle potential whitespace/newlines
        input_str = sys.stdin.read().strip()
        if not input_str:
             sys.exit(-1)
             
        index = int(input_str)
        
        # Function handles bounds check
        result = get_value_from_array(id_sequence, size, index)
        
    except ValueError:
        result = -1
    except Exception:
        result = -1

    sys.exit(result)

if __name__ == "__main__":
    main()
