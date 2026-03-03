# Python's built-in print() needs no import — it is always available.
# The two imports below mirror the C pattern (I/O + stdlib) as explicit examples.

import sys   # provides sys.stdout, sys.stderr, sys.argv, sys.exit — the I/O/runtime module
import os    # provides os.path, os.environ, os.getcwd — the standard library OS utilities

# print() is a built-in; sys and os are only imported to illustrate the mechanism
print("Imports loaded: sys (I/O and runtime) and os (standard library utilities).")
