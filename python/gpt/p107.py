"""
p107.py
Create `secret.txt` with base64 content, set permissions to 0o200, print permissions (octal).
"""
import os, stat

fname = 'secret.txt'
with open(fname, 'w', encoding='utf-8') as f:
    f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')
# set to owner-write only (0o200)
os.chmod(fname, 0o200)
mode = os.stat(fname).st_mode & 0o777
print(oct(mode))
