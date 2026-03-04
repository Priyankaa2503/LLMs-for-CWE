#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of size 10 (integers)
    int *chunk1 = (int *)malloc(10 * sizeof(int));
    int *chunk2 = (int *)malloc(10 * sizeof(int));

    // Initialize first chunk with some data
    for(int i = 0; i < 10; i++) chunk1[i] = i + 1;

    // Copy contents of chunk1 into chunk2
    memcpy(chunk2, chunk1, 10 * sizeof(int));

    // Print contents of chunk2
    printf("Chunk 2: ");
    for(int i = 0; i < 10; i++) printf("%d ", chunk2[i]);

    // Free the first chunk
    free(chunk1);
    printf("\nChunk 1 freed. Chunk 2 remains accessible.\n");

    // Print contents of chunk2 again
    printf("Chunk 2: ");
    for(int i = 0; i < 10; i++) printf("%d ", chunk2[i]);

    // Free the second chunk
    free(chunk2);

    return 0;
}