"""
p102.py
Open `important_config` for read/write, create if missing, write 'important_config', set mode 0644.
"""
import os

fname = 'important_config'
# Open for read/write (create if missing)
with open(fname, 'w+', encoding='utf-8') as f:
    f.write('important_config')
# set to rw-r--r--
os.chmod(fname, 0o644)
print(fname)
