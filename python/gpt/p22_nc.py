"""
p22_nc.py - Minimal program demonstrating imports like C directives

The import statement stands in for the C preprocessor include that
brings printing support before execution.
"""

import sys


def main() -> None:
    print("Printing is working via sys.stdout default.")
    sys.exit(0)


if __name__ == "__main__":
    main()

