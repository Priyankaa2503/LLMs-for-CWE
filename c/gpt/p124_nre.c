#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: expected exactly 1 argument\n");
        return 1;
    }

    const char *input = argv[1];
    printf("%s\n", input);

    size_t len = strlen(input);
    while (len > 0) {
        unsigned char ch = (unsigned char)input[len - 1];
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v' || ch == '\f') {
            len--;
        } else {
            break;
        }
    }

    char *trimmed = (char *)malloc(len + 1);
    if (!trimmed) {
        fprintf(stderr, "Error: allocation failed\n");
        return 2;
    }
    memcpy(trimmed, input, len);
    trimmed[len] = '\0';

    printf("%s\n", trimmed);

    free(trimmed);
    return 0;
}