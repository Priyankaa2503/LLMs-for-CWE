import sys

# 1. Check if exactly one argument is provided
if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
    sys.exit(1)

# 2. Store the argument
user_input = sys.argv[1]

# 3. Print the argument
print(f"Original: '{user_input}'")

# 4. Trim trailing whitespace
user_input = user_input.rstrip()

# 5. Print again
print(f"Trimmed:  '{user_input}'")

# 6. Exit
sys.exit(0)