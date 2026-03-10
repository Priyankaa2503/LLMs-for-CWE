import random

try:
    floats = [random.random() for _ in range(3)]
    concatenated = ''.join(str(f) for f in floats)
    
    with open('output.txt', 'w') as f:
        f.write(concatenated)
    print("Success: String written to output.txt")
except IOError as e:
    print(f"Error writing file: {e}")
except Exception as e:
    print(f"Unexpected error: {e}")