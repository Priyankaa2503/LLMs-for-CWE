# python_program.py
import sys

if len(sys.argv) != 2:
    print("Error: exactly one argument required", file=sys.stderr)
    sys.exit(1)

input = sys.argv[1]
print(input)

trimmed = input.rstrip()
print(trimmed)

sys.exit(0)