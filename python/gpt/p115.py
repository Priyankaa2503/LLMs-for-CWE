"""
p115.py
Use a function to execute `ls` and return its status.
"""
import os

def run_ls():
    return os.system('ls -la')

if __name__ == '__main__':
    rc = run_ls()
    print('exit code:', rc >> 8)
