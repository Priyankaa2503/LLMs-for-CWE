# Python
import random
import os

output_file = "output.txt"
try:
    floats = [random.uniform(0, 1) for _ in range(3)]
    float_strings = [str(f) for f in floats]
    concatenated = "".join(float_strings)
    
    with open(output_file, "w", encoding="utf-8") as f:
        f.write(concatenated)
    os.chmod(output_file, 0o600)
except IOError as e:
    print(f"Error writing to file: {e}")