# Python: Secure directory listing using pathlib
from pathlib import Path
import sys

path = Path(sys.argv[1]) if len(sys.argv) > 1 else Path(".")

try:
    if not path.is_dir():
        raise NotADirectoryError(f"{path} is not a directory")
    
    for entry in path.iterdir():
        print(entry.name)
        
except (OSError, NotADirectoryError) as e:
    print(f"Error: {e}", file=sys.stderr)
    sys.exit(1)