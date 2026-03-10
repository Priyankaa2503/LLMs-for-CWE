# PYTHON - SystemRandom (cryptographically secure)
import random

rand = random.SystemRandom()
float_a = rand.random() * 100
float_b = rand.random() * 100
float_c = rand.random() * 100

str_a = f"{float_a:.6f}"
str_b = f"{float_b:.6f}"
str_c = f"{float_c:.6f}"