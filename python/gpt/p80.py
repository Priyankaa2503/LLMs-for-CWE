#!/usr/bin/env python3
import sys

"""
Reads a line from stdin up to 1023 characters (buffer 1024).
Simulates the behavior where the newline is consumed but not stored.
"""

def main():
    print('Enter a line (up to 1023 chars):')
    # readline(1024) reads at most 1023 characters plus the newline if present
    data = sys.stdin.readline(1024)
    if data == '':
        print('No input or EOF')
        return

    # If newline present, remove it from stored buffer (newline not stored)
    if data.endswith('\n'):
        stored = data[:-1]
        newline_consumed = True
    else:
        stored = data
        newline_consumed = False

    # Ensure buffer behaves like a 1024-byte buffer storing at most 1023 chars
    stored = stored[:1023]

    print('Read length (excluding newline):', len(stored))
    print('Stored string:', stored)
    print('Newline consumed:', newline_consumed)

if __name__ == '__main__':
    main()
