# p26: loop 3 times calling getMonthlySales(i) and sum for first quarter
import random


def getMonthlySales(i):
    return random.randint(0, 100000)


def main():
    total = 0
    for i in range(3):
        total += getMonthlySales(i)
    print(f"Q1 total: {total}")


if __name__ == "__main__":
    main()
