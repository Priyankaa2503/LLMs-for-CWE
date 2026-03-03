id_sequence = [10, 20, 30, 40, 50]

def get_value(index):
    if not isinstance(index, int) or isinstance(index, bool):
        return -1
    if index < 0 or index >= len(id_sequence):
        return -1
    return id_sequence[index]

def main():
    try:
        raw = input("Enter an index: ").strip()
        index = int(raw)
    except (ValueError, EOFError):
        print("Invalid input. Result: -1")
        return
    print(f"Result: {get_value(index)}")

main()