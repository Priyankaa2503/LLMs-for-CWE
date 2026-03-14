import secrets

def float_to_str(val):
    if not (float('-inf') < val < float('inf')):
        return "0.0"
    return "{:.6f}".format(val)

# Using secrets for cryptographically secure random floats
generator = secrets.SystemRandom()
str_a = float_to_str(generator.uniform(0, 100))
str_b = float_to_str(generator.uniform(0, 100))
str_c = float_to_str(generator.uniform(0, 100))