"""
p109.py
Read /etc/passwd and print lines matching username provided as argv[1]
"""
import sys

if len(sys.argv) < 2:
    print('usage: p109.py username')
    sys.exit(1)
user = sys.argv[1]
with open('/etc/passwd', 'r', encoding='utf-8') as f:
    for line in f:
        if user in line:
            print(line, end='')
