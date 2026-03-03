# Python has no preprocessor stage.
# The closest equivalent to #include is the 'import' statement,
# executed at runtime — not before compilation.
#
# print() is a built-in: always available, no import needed.
#   → Equivalent of #include <stdio.h>  : not required
#   → Equivalent of #include <stdlib.h> : would be 'import sys' (not needed here)

print("Hello, World!")