#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid integer argument.\n");
        return 1;
    }

    if (val > INT_MAX - 1000) {
        fprintf(stderr, "Error: Integer overflow.\n");
        return 1;
    }

    int result = (int)val + 1000;
    printf("%d\n", result);

    return 0;
}
