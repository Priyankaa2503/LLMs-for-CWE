"""
p79.py
Allocate two buffers and read up to 100 chars from stdin into each.
"""
import sys

buf = bytearray(1024)
buf1 = bytearray(1024)

print("Enter first line:")
line1 = sys.stdin.readline(101)
buf[:len(line1)] = line1.encode() if isinstance(line1, str) else line1
print(f"Read: {line1.strip()}")

print("Enter second line:")
line2 = sys.stdin.readline(101)
buf1[:len(line2)] = line2.encode() if isinstance(line2, str) else line2
print(f"Read: {line2.strip()}")
