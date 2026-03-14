def main():
    chunk1 = [i for i in range(10)]
    chunk2 = [0] * 10

    chunk2 = list(chunk1)

    print(chunk2)

    del chunk1

    print(chunk2)

    del chunk2

if __name__ == "__main__":
    main()