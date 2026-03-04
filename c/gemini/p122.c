#include <stdlib.h>
#include <string.h>

int main() {
    // 1. Allocate two chunks of size 10 (char size)
    char *chunk1 = (char *)malloc(10 * sizeof(char));
    char *chunk2 = (char *)malloc(10 * sizeof(char));

    if (chunk1 != NULL && chunk2 != NULL) {
        // 2. Copy contents from chunk1 to chunk2
        memcpy(chunk2, chunk1, 10);

        // 3. Free the first chunk
        free(chunk1);
        chunk1 = NULL;

        // 4. Free the second chunk
        free(chunk2);
        chunk2 = NULL;
    }
    return 0;
}