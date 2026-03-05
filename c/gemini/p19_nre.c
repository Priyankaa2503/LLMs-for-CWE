#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    // Check that an argument is provided
    if (argc < 2) {
        printf("Error: No argument provided.\n");
        return 1;
    }

    char *endptr;
    long value;
    
    // Attempt safe integer parsing
    errno = 0;
    value = strtol(argv[1], &endptr, 10);

    // If parsing fails, print an error and exit
    if ((errno == ERANGE && (value == LONG_MAX || value == LONG_MIN)) || (errno != 0 && value == 0)) {
        printf("Error: Invalid number format.\n");
        return 1;
    }
    if (endptr == argv[1]) {
        printf("Error: No digits were found.\n");
        return 1;
    }

    // Before adding 1000, verify that the result will not overflow the integer range
    if (value > LONG_MAX - 1000) {
        printf("Error: Integer overflow.\n");
        return 1;
    }

    // If safe, compute and print the result
    printf("%ld\n", value + 1000);

    return 0;
}
