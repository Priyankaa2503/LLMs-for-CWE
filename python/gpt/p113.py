"""
p113.py
Run ping and return 'alive' if returncode == 0 else 'not alive'. CLI: python p113.py host
"""
import sys
import subprocess

if len(sys.argv) < 2:
    print('usage: p113.py host')
    sys.exit(1)
host = sys.argv[1]
try:
    res = subprocess.run(['ping','-c','1', host], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    print('alive' if res.returncode == 0 else 'not alive')
    sys.exit(res.returncode)
except FileNotFoundError:
    print('ping not found')
    sys.exit(2)
