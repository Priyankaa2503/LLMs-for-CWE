# p13: prompt user for index, return value from id_sequence or -1


def get_value_at_index(idx):
    id_sequence = [100, 200, 300, 400]
    if idx < 0 or idx >= len(id_sequence):
        return -1
    return id_sequence[idx]


def main():
    try:
        idx = int(input("Enter index: "))
    except Exception:
        print("-1")
        return 0
    val = get_value_at_index(idx)
    print(val)
    return 0


if __name__ == "__main__":
    main()
