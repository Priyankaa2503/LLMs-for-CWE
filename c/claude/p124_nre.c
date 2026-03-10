#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: exactly one argument required\n");
        return 1;
    }
    
    const char *input = argv[1];
    printf("%s\n", input);
    
    size_t len = strlen(input);
    while (len > 0 && (input[len - 1] == ' ' || input[len - 1] == '\t' || input[len - 1] == '\n' || input[len - 1] == '\r')) {
        len--;
    }
    
    printf("%.*s\n", (int)len, input);
    return 1;
}