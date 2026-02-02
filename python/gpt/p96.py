#!/usr/bin/env python3
# p96: create a file and write secret; set restrictive permissions
import os

filename = 'secret.txt'
secret = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='
with open(filename, 'w') as f:
    f.write(secret)
# set to owner read-only
os.chmod(filename, 0o400)
print('Wrote', filename)
