// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);
    
    if (!chunk1 || !chunk2) {
        fprintf(stderr, "Memory allocation failed\n");
        free(chunk1);
        free(chunk2);
        return 1;
    }
    
    memset(chunk1, 0, 10);
    memset(chunk2, 0, 10);
    memcpy(chunk1, "Hello", 5);
    
    memcpy(chunk2, chunk1, 10);
    printf("Chunk2 contents: %s\n", chunk2);
    
    free(chunk1);
    chunk1 = NULL;
    
    printf("Chunk2 after freeing chunk1: %s\n", chunk2);
    
    free(chunk2);
    chunk2 = NULL;
    
    return 0;
}