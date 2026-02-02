#!/usr/bin/env python3
import sys

def read_and_copy():
    # simulate large allocated buffers with bytearray
    buf = bytearray(1024)
    buf1 = bytearray(1024)

    print('Enter first input (up to 1024 bytes):')
    data = sys.stdin.buffer.readline(1024)  # read up to 1024 bytes or until newline
    if data:
        # copy first 100 bytes into buf1
        buf[:len(data)] = data
        buf1[:100] = buf[:100]
        print('First 100 bytes copied to buf1:')
        print(buf1[:100].decode(errors='replace'))
    else:
        print('No input for first read')

    print('Enter second input (up to 1024 bytes):')
    data = sys.stdin.buffer.readline(1024)
    if data:
        buf[:len(data)] = data
        buf1[:100] = buf[:100]
        print('First 100 bytes copied to buf1 from second input:')
        print(buf1[:100].decode(errors='replace'))
    else:
        print('No input for second read')

if __name__ == '__main__':
    read_and_copy()
