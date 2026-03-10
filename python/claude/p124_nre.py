import sys

if len(sys.argv) != 2:
    print("Error: exactly one argument required", file=sys.stderr)
    sys.exit(1)

input_str = sys.argv[1]
print(input_str)
trimmed = input_str.rstrip()
print(trimmed)
sys.exit(0)