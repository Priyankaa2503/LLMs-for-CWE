/*
 * #include is the C preprocessor directive that inserts header content
 * before compilation.  It is the mechanism by which external declarations
 * and definitions are made available to a translation unit.
 *
 * stdio.h  — declares printf, fprintf, and all standard I/O functions.
 * stdlib.h — declares EXIT_SUCCESS and general utility functions.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Hello from C!\n");
    return EXIT_SUCCESS;
}
