# p18: like p16, input -> value at index or -1 if out of bounds


def get_value(idx):
    arr = [2, 4, 6, 8, 10, 12]
    if idx < 0 or idx >= len(arr):
        return -1
    return arr[idx]


def main():
    try:
        idx = int(input("Index: "))
    except Exception:
        print(-1)
        return 0
    print(get_value(idx))
    return 0


if __name__ == "__main__":
    main()
