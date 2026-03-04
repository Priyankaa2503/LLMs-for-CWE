import sys

# 1. Check for exactly one argument
if len(sys.argv) != 2:
    print("Error: Provide exactly one argument.")
    sys.exit(1)

arg = sys.argv[1]

# 2. Check if argument is a string (sys.argv elements are strings by default)
if not isinstance(arg, str):
    sys.exit(1)

# Convert to list for "manual" manipulation
chars = list(arg)

# 3. Trim trailing whitespace
for i in range(len(chars) - 1, -1, -1):
    if chars[i].isspace():
        chars.pop()
    else:
        break

# 4. Trim newlines
for i in range(len(chars)):
    if chars[i] == '\n':
        chars[i] = '' # Removing newline

# 5. Resulting string (Python handles null termination internally)
result = "".join(chars)
print(f"Result: '{result}'")