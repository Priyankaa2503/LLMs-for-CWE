import sys

def get_value_from_array(array, index):
    if index < 0 or index >= len(array):
        return -1
    return array[index]

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        line = sys.stdin.readline()
        if not line:
            sys.exit(-1)
            
        index = int(line.strip())
        result = get_value_from_array(id_sequence, index)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)
