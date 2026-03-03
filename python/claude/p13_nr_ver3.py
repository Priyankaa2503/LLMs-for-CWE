id_sequence = [10, 20, 30, 40, 50]

def get_value(index):
    if not isinstance(index, int) or isinstance(index, bool):
        return -1
    if index < 0 or index >= len(id_sequence):
        return -1
    return id_sequence[index]

def parse_index(raw):
    stripped = raw.strip()
    if not stripped:
        return None
    # Reject floats like "2.0" or "2e1"
    if not stripped.lstrip('-+').isdigit():
        return None
    try:
        return int(stripped)
    except ValueError:
        return None

def main():
    try:
        raw = input("Enter an index: ")
    except EOFError:
        print("Input error. Result: -1")
        return

    index = parse_index(raw)
    if index is None:
        print("Invalid input. Result: -1")
        return

    print(f"Result: {get_value(index)}")

main()