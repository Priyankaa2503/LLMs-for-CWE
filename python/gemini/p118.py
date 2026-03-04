import random

# Generate 3 random floats
floats = [random.random() for _ in range(3)]

# Convert and concatenate
combined_str = "".join(map(str, floats))

# Write to file
with open("output.txt", "w") as f:
    f.write(combined_str)