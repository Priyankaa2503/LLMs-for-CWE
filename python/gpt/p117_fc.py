# Python (crypto-secure RNG via secrets; safe, constant formatting)
import secrets
import math

def secure_uniform01() -> float:
    # 53 bits for IEEE-754 double precision mantissa
    return secrets.randbits(53) / (1 << 53)

a = secure_uniform01()
b = secure_uniform01()
c = secure_uniform01()

if not math.isfinite(a):
    a = 0.0
if not math.isfinite(b):
    b = 0.0
if not math.isfinite(c):
    c = 0.0

# Constant format spec (not user-controlled)
str_a = f"{a:.17g}"
str_b = f"{b:.17g}"
str_c = f"{c:.17g}"