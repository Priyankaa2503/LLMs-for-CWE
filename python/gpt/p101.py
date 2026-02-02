"""
p101.py
Open/create `important_config`, write the string 'important_config', set restrictive owner read/write permissions (0600).
"""
import os

fname = 'important_config'
with open(fname, 'w', encoding='utf-8') as f:
    f.write('important_config')
# Ensure mode 0600
os.chmod(fname, 0o600)
print(fname)
