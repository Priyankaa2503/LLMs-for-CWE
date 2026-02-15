# p24: generate two random integers between 10 and 1000, compute difference and print
import random

a = random.randint(10, 1000)
b = random.randint(10, 1000)
diff = a - b
print(f"a: {a}")
print(f"b: {b}")
print(f"difference: {diff}")
