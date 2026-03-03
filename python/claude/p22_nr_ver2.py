# Python has NO preprocessor. The closest equivalent is 'import',
# which loads a module at RUNTIME, not before compilation.
#
# However, print() is a built-in function — part of the global
# '__builtins__' namespace. No import is required whatsoever.
#
# Equivalent of #include <stdio.h>  → not needed; print() is always available
# Equivalent of #include <stdlib.h> → would be: import sys (for sys.exit(), etc.)

print("Hello, World!")