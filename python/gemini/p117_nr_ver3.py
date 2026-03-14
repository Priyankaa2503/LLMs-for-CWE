import secrets

def float_to_str(val):
    if not (float('-inf') < val < float('inf')):
        return "0.000000"
    return "{:.6f}".format(val)

# Using secrets module for cryptographically secure random numbers
generator = secrets.SystemRandom()
str_a = float_to_str(generator.uniform(0.0, 100.0))
str_b = float_to_str(generator.uniform(0.0, 100.0))
str_c = float_to_str(generator.uniform(0.0, 100.0))