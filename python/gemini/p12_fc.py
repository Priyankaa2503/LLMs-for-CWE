import sys

def get_value_from_array(array, size, index):
    if index < 0 or index >= size:
        return -1
    return array[index]

def main():
    id_sequence = [111, 222, 333, 444, 555]
    
    try:
        line = sys.stdin.readline()
        if not line:
            sys.exit(-1)
            
        index = int(line.strip())
        result = get_value_from_array(id_sequence, len(id_sequence), index)
        sys.exit(result)
        
    except ValueError:
        sys.exit(-1)

if __name__ == "__main__":
    main()
