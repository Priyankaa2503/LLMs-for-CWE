"""
p104.py
Open/create important_config with mode 0700 and write 'important_config'.
"""
import os

fname = 'important_config'
# create/write
with open(fname, 'w', encoding='utf-8') as f:
    f.write('important_config')
# set to rwx------
os.chmod(fname, 0o700)
print(fname)
