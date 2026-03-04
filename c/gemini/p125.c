#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        char *arg = argv[1];
        int len = strlen(arg);

        // Move backward from the end and replace whitespace with null terminator
        while (len > 0 && isspace((unsigned char)arg[len - 1])) {
            arg[--len] = '\0';
        }

        printf("%s\n", arg);
    }
    return 0;
}