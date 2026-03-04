#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    // 1. Check for exactly one argument (plus the program name)
    if (argc != 2) {
        printf("Error: Please provide exactly one argument.\n");
        return 1;
    }

    char *str = argv[1];
    int len = strlen(str);

    // 2. Argument is naturally a char* in C (string)

    // 3. Trim trailing whitespace
    for (int i = len - 1; i >= 0 && isspace(str[i]); i--) {
        str[i] = '\0';
        len--;
    }

    // 4. Trim newlines (if any remain)
    for (int i = 0; i < len; i++) {
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = ' '; // Replacing or shifting logic
        }
    }

    // 5. Explicitly null terminate
    str[len] = '\0';

    printf("Result: '%s'\n", str);
    return 0;
}