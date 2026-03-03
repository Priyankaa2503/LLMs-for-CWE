import sys

id_sequence = [10, 20, 30, 40, 50]

def get_value_from_array(arr, size, index):
    if not arr or size <= 0 or not isinstance(index, int) or index < 0 or index >= size:
        return -1
    return arr[index]

def main():
    raw = sys.stdin.readline().strip()
    if not raw:
        sys.exit(-1)

    try:
        index = int(raw)
    except ValueError:
        sys.exit(-1)

    result = get_value_from_array(id_sequence, len(id_sequence), index)
    sys.exit(result)

if __name__ == "__main__":
    main()