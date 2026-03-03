# Python's analogue of a C preprocessor #include is the import statement.
# Built-in functions such as print() require no import at all.
# The sys module is part of the standard library and is imported here
# to demonstrate the import mechanism; it is not required for printing.
import sys  # provides sys.stdout, sys.argv, sys.exit, etc.

# print() writes to stdout; no import is required for basic output.
print("Hello from Python!")

# Explicitly flush stdout (good practice in piped or scripted environments).
sys.stdout.flush()
