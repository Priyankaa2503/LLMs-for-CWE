"""
p80.py
Read input using readline (which strips newline) with up to 1023 chars.
"""
import sys

print("Enter a string:")
line = sys.stdin.readline(1024).rstrip('\n')
print(f"Read {len(line)} char(s): {line}")
