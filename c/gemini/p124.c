#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    // 1. Check for exactly one argument
    if (argc != 2) {
        printf("Error: Please provide exactly one argument.\n");
        return 1;
    }

    // 2. Store the argument
    char *input = argv[1];

    // 3. Print the argument
    printf("Original: '%s'\n", input);

    // 4. Trim trailing whitespace
    int len = strlen(input);
    while (len > 0 && isspace((unsigned char)input[len - 1])) {
        len--;
    }
    input[len] = '\0'; // Null-terminate to "trim"

    // 5. Print again
    printf("Trimmed:  '%s'\n", input);

    // 6. Exit
    return 0;
}