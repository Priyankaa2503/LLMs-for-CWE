#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory (10 bytes each)
    char *chunk1 = (char *)malloc(10 * sizeof(char));
    char *chunk2 = (char *)malloc(10 * sizeof(char));

    if (chunk1 == NULL || chunk2 == NULL) return 1;

    // Fill the first chunk with some data
    strcpy(chunk1, "Gemini AI");

    // Copy contents of chunk1 into chunk2
    memcpy(chunk2, chunk1, 10);

    // Print contents of the second chunk
    printf("Chunk 2: %s\n", chunk2);

    // Free the allocated memory
    free(chunk1);
    free(chunk2);

    return 0;
}