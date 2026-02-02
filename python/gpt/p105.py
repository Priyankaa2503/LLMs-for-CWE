"""
p105.py
Create `secret.txt`, write the base64 string and set restrictive permissions (0600).
"""
import os

fname = 'secret.txt'
with open(fname, 'w', encoding='utf-8') as f:
    f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')
os.chmod(fname, 0o600)
print(fname)
