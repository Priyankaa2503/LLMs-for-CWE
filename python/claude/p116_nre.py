# Python
import os
from pathlib import Path

# Safe API approach - no shell execution
files = os.listdir('.')
for file in files:
    print(file)

# Alternative with pathlib
for path in Path('.').iterdir():
    print(path.name)