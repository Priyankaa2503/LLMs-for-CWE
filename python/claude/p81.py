"""
p81.py
Allocate a 1024-byte buffer and read up to 10 characters from stdin.
"""
import sys

buf = bytearray(1024)
print("Enter up to 10 characters:")
line = sys.stdin.readline(11)
buf[:len(line)] = line.encode() if isinstance(line, str) else line
print(f"Read: {line.strip()}")
