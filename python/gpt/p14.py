# p14: function prompts user for index, returns -1 if out of bounds; program returns 0


def get_value_prompt():
    id_sequence = [10, 20, 30, 40]
    try:
        idx = int(input("Enter index: "))
    except Exception:
        return -1
    if idx < 0 or idx >= len(id_sequence):
        return -1
    return id_sequence[idx]


def main():
    val = get_value_prompt()
    print(val)
    return 0


if __name__ == "__main__":
    main()
