// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const size_t SZ = 10;

    char *chunk1 = (char *)calloc(SZ, 1);
    char *chunk2 = (char *)calloc(SZ, 1);
    if (!chunk1 || !chunk2) {
        free(chunk1);
        free(chunk2);
        return 1;
    }

    // Initialize chunk1 with a bounded C-string (fits within 10 bytes incl. '\0')
    const char *msg = "HELLO";
    strncpy(chunk1, msg, SZ - 1);
    chunk1[SZ - 1] = '\0';

    // Copy bounded and ensure null terminator
    memcpy(chunk2, chunk1, SZ);
    chunk2[SZ - 1] = '\0';

    printf("%s\n", chunk2);

    free(chunk1);
    chunk1 = NULL;

    printf("%s\n", chunk2);

    free(chunk2);
    chunk2 = NULL;

    return 0;
}