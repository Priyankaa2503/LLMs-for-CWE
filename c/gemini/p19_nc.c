#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: Please provide an integer argument.\n");
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || endptr == argv[1]) {
        printf("Error: Invalid integer input.\n");
        return 1;
    }

    // Check for overflow before adding 1000
    if (val > INT_MAX - 1000) {
        printf("Error: Integer overflow would occur.\n");
        return 1;
    }

    int result = (int)val + 1000;
    printf("%d\n", result);

    return 0;
}
