// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: expected exactly 1 argument.\n");
        return 1;
    }

    char *input = argv[1];
    printf("%s\n", input);

    size_t len = strlen(input);
    char *buf = (char *)malloc(len + 1);
    if (!buf) {
        fprintf(stderr, "Error: out of memory.\n");
        return 1;
    }
    memcpy(buf, input, len + 1);

    while (len > 0 && isspace((unsigned char)buf[len - 1])) {
        buf[len - 1] = '\0';
        len--;
    }

    printf("%s\n", buf);
    free(buf);
    return 0;
}