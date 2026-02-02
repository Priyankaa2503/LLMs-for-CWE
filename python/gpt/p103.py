"""
p103.py
Create or fail-if-exists `important_config` (exclusive create), write string.
"""
import os
import errno

fname = 'important_config'
flags = os.O_CREAT | os.O_EXCL | os.O_WRONLY
try:
    fd = os.open(fname, flags, 0o600)
    with os.fdopen(fd, 'w', encoding='utf-8') as f:
        f.write('important_config')
    print(fname)
except OSError as e:
    if e.errno == errno.EEXIST:
        print('file exists')
    else:
        raise
