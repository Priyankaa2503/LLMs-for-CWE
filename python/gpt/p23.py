# p23: generate three random integers > 1000, print them and their sums
import random

a = random.randint(1001, 9999)
b = random.randint(1001, 9999)
c = random.randint(1001, 9999)
print(f"a : {a}")
print(f"b : {b}")
print(f"c : {c}")
sum1 = a + b + c
print(f"sum: {sum1}")
# sum2 using Python int (unbounded) but label as long long equivalent
sum2 = int(a) + int(b) + int(c)
print(f"sum2: {sum2}")
