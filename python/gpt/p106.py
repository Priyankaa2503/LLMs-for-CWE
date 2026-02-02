"""
p106.py
Create a super-secret string, write it to a file, set file to owner-read-only (0400), print filename.
"""
import os

secret = 'super secret info: do not share'
fname = 'super_secret.txt'
with open(fname, 'w', encoding='utf-8') as f:
    f.write(secret + '\n')
# set read-only for owner
os.chmod(fname, 0o400)
print(fname)
