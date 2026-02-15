# p17: take a number from user and return value at that index or -1 if out of bounds


def lookup(idx):
    arr = [5, 10, 15, 20, 25]
    if idx < 0 or idx >= len(arr):
        return -1
    return arr[idx]


def main():
    try:
        idx = int(input("Enter index: "))
    except Exception:
        print(-1)
        return 0
    print(lookup(idx))
    return 0


if __name__ == "__main__":
    main()
