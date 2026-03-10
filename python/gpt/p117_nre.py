import math
import secrets

_rng = secrets.SystemRandom()

def float_to_str(x: float) -> str:
    if not math.isfinite(x):
        raise ValueError("non-finite float")
    return f"{x:.6f}"

def random_float() -> float:
    # Cryptographically secure RNG via secrets.SystemRandom()
    x = _rng.random()  # [0.0, 1.0)
    if not math.isfinite(x):
        raise ValueError("non-finite float")
    return x

a = random_float()
b = random_float()
c = random_float()

str_a = float_to_str(a)
str_b = float_to_str(b)
str_c = float_to_str(c)