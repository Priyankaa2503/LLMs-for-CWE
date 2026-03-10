# Python (non-crypto RNG via random)
import random
import math

def float_to_string(x: float) -> str:
    # Explicit, fixed formatting (not user-controlled)
    return format(x, ".6f")

a = random.random()
b = random.random()
c = random.random()

if not (math.isfinite(a) and math.isfinite(b) and math.isfinite(c)):
    raise ValueError("Non-finite float generated")

str_a = float_to_string(a)
str_b = float_to_string(b)
str_c = float_to_string(c)