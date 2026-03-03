// Preprocessor directive: tells the C preprocessor to include the
// stdio.h header before compilation. This provides printf().
#include <stdio.h>

// Preprocessor directive: includes stdlib.h for EXIT_SUCCESS constant,
// which is the safe, portable way to signal successful program exit.
#include <stdlib.h>

int main(void) {
    printf("Hello, World!\n");
    return EXIT_SUCCESS;
}