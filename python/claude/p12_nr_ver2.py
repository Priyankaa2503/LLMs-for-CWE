import sys

def getValueFromArray(arr, size, index):
    if not arr or size <= 0 or index < 0 or index >= size:
        return -1
    return arr[index]

def main():
    arr = [10, 20, 30, 40, 50]
    size = len(arr)

    try:
        line = input().strip()
        index = int(line)
    except (ValueError, EOFError):
        sys.exit(255)

    result = getValueFromArray(arr, size, index)
    sys.exit(255 if result == -1 else result)

if __name__ == "__main__":
    main()