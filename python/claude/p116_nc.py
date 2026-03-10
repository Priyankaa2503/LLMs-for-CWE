# Python - Using pathlib (recommended) and os.listdir
from pathlib import Path
import sys

# Preferred: Using pathlib
try:
    files = list(Path('.').iterdir())
    for file in sorted(files):
        print(file.name)
except Exception as e:
    print(f"Error listing directory: {e}", file=sys.stderr)
    sys.exit(1)

# Alternative: Using os.listdir
import os
try:
    files = os.listdir('.')
    for file in sorted(files):
        print(file)
except OSError as e:
    print(f"Error listing directory: {e}", file=sys.stderr)
    sys.exit(1)