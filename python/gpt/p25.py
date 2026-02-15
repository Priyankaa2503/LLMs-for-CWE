# p25: call getMonthlySales 12 times, sum quarterly and print
import random


def getMonthlySales(month_index):
    # return random between 0 and 100000
    return random.randint(0, 100000)


def main():
    months = [getMonthlySales(i) for i in range(12)]
    for i, val in enumerate(months):
        print(f"Month {i+1}: {val}")
    q_sums = [sum(months[i * 3 : (i + 1) * 3]) for i in range(4)]
    for i, qs in enumerate(q_sums):
        print(f"Quarter {i+1} sum: {qs}")


if __name__ == "__main__":
    main()
