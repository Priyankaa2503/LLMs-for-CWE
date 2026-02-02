#!/usr/bin/env python3
# p92: simple registration-like hashing example (same as p91 but focused on hashing)
import hashlib, os

def hash_password(password):
    salt = os.urandom(16)
    h = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt, h

if __name__=='__main__':
    import sys
    if len(sys.argv)<2:
        print('Usage: p92.py <password>')
        sys.exit(1)
    s,h = hash_password(sys.argv[1])
    print('salt:', s.hex())
    print('hash:', h.hex())
