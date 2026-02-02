"""
p108.py
Run `getent passwd <username>` and print the output.
Usage: python3 python/gpt/p108.py username
"""
import sys
import subprocess

if len(sys.argv) < 2:
    print('usage: p108.py username')
    sys.exit(1)
user = sys.argv[1]
try:
    res = subprocess.run(['getent','passwd',user], capture_output=True, text=True)
    print(res.stdout, end='')
    sys.exit(res.returncode)
except FileNotFoundError:
    print('getent not found on this system')
    sys.exit(2)
