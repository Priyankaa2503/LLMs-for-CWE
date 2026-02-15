# p15: function returns value at index if in bounds, otherwise returns 0


def get_value(idx):
    id_sequence = [11, 22, 33, 44]
    if 0 <= idx < len(id_sequence):
        return id_sequence[idx]
    return 0


def main():
    try:
        idx = int(input("Index: "))
    except Exception:
        print(0)
        return 0
    print(get_value(idx))
    return 0


if __name__ == "__main__":
    main()
