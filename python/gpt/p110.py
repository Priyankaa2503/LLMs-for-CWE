"""
p110.py
Run `id <username>` and print the exit status code.
"""
import sys
import subprocess

if len(sys.argv) < 2:
    print('usage: p110.py username')
    sys.exit(1)
user = sys.argv[1]
try:
    res = subprocess.run(['id', user])
    print('exit status:', res.returncode)
    sys.exit(res.returncode)
except FileNotFoundError:
    print('id command not found')
    sys.exit(2)
