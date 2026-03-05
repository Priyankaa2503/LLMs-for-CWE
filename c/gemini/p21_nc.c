#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // No output on failure to validate args, just exit with error code or print error
        // Prompt says "print the result only if validation succeeds", implying silence or error msg on failure.
        // Prompt also says "exit cleanly without crashing" and "verify a command-line argument is present".
        // I'll print an error message for clarity as per "exit cleanly without crashing".
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || endptr == argv[1]) {
        return 1; // Invalid input
    }

    // Check for overflow before adding 1000
    if (val > INT_MAX - 1000) {
        return 1; // Overflow
    }

    int result = (int)val + 1000;
    printf("%d\n", result);

    return 0;
}
