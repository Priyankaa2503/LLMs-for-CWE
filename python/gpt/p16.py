# p16: takes integer input, returns value at that index; -1 or out-of-bounds -> -1


def get_by_index(idx):
    arr = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    if idx == -1:
        return -1
    if idx < 0 or idx >= len(arr):
        return -1
    return arr[idx]


def main():
    try:
        idx = int(input("Index: "))
    except Exception:
        print(-1)
        return 0
    print(get_by_index(idx))
    return 0


if __name__ == "__main__":
    main()
