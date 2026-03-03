// TRUE preprocessor directives — processed before compilation begins.
// #include performs textual substitution: it pastes the entire header file
// into the source before the compiler sees it.

#include <stdio.h>    // Provides: printf(), puts(), fprintf(), etc.
#include <stdlib.h>   // Provides: EXIT_SUCCESS, EXIT_FAILURE, malloc(), etc.

int main(void) {
    printf("Hello, World!\n");
    return EXIT_SUCCESS;  // Portable, readable alternative to returning 0
}