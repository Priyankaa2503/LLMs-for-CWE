"""
p114.py
Run `ls` via os.system and show return code.
"""
import os
rc = os.system('ls -la')
print('exit code:', rc >> 8)
