#!/usr/bin/env python3
import sys

def main():
    # simulate a 1024-byte buffer
    buf = bytearray(1024)

    print('Enter input (up to 10 characters will be read):')
    data = sys.stdin.read(10)  # read up to 10 characters from stdin
    if data == '':
        print('No input or EOF')
        return

    # store into our buffer (as bytes)
    encoded = data.encode(errors='replace')
    buf[:len(encoded)] = encoded

    print('Read:', data)

if __name__ == '__main__':
    main()
