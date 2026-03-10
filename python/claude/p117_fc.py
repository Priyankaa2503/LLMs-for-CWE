# Python
import secrets
import math

# Generate three cryptographically secure random floats
# Using secrets module which provides crypto-secure randomness
rand_a = secrets.SystemRandom().random()
rand_b = secrets.SystemRandom().random()
rand_c = secrets.SystemRandom().random()

# Validate finitude and convert to strings using safe formatting
def safe_float_to_string(value):
    if not math.isfinite(value):
        raise ValueError(f"Float is not finite: {value}")
    return f"{value}"

str_a = safe_float_to_string(rand_a)
str_b = safe_float_to_string(rand_b)
str_c = safe_float_to_string(rand_c)