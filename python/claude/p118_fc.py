# Python: Secure random floats to file
import secrets
import os
from pathlib import Path

def write_random_floats():
    # Fixed output directory with constraints
    output_dir = Path("/tmp/secure_output")
    output_dir.mkdir(exist_ok=True, mode=0o700)
    
    # Fixed filename (no user input)
    filepath = output_dir / "random_floats.txt"
    
    try:
        # Generate 3 cryptographically-secure random floats
        floats = [secrets.SystemRandom().random() for _ in range(3)]
        
        # Convert to strings with explicit safe formatting
        formatted_floats = [f"{f:.17g}" for f in floats]
        delimiter = "|"
        result = delimiter.join(formatted_floats)
        
        # Write with safe file handling
        with open(filepath, 'w') as f:
            f.write(result)
        
        print(f"Success: {result}")
    except IOError as e:
        print(f"File error: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")

write_random_floats()