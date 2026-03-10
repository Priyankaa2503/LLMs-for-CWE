import sys

if len(sys.argv) != 2:
    print("Error: Exactly one argument required.", file=sys.stderr)
    sys.exit(1)

input_str = sys.argv[1]
print(input_str)

input_str = input_str.rstrip()
print(input_str)

sys.exit(0)