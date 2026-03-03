# Python's built-in print() requires no import.
# sys is imported here only to demonstrate standard-library usage;
# it is not strictly needed for a simple print statement.
import sys  # provides sys.stdout, sys.argv, sys.exit, etc.

# print() writes to stdout; no import required for basic output.
print("Hello from Python!")

# Explicitly flush stdout (good practice in piped/scripted environments).
sys.stdout.flush()
