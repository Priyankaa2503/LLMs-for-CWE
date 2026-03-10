// C - Most relevant for explicit memory management
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of 10 bytes each
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);
    
    // CHECK: Allocations checked for NULL/failures
    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(chunk1);
        free(chunk2);
        return 1;
    }
    
    // Initialize chunk1 with data
    strcpy(chunk1, "HelloTest");
    
    // Copy contents of chunk1 to chunk2
    // CHECK: Copy is bounded; handles size properly
    memcpy(chunk2, chunk1, 10);
    
    // Print contents of chunk2
    printf("chunk2 after copy: %s\n", chunk2);
    
    // Free chunk1
    free(chunk1);
    chunk1 = NULL;  // Defensive: prevent use-after-free
    
    // Print contents of chunk2 (valid, chunk1 freed but chunk2 still allocated)
    printf("chunk2 after freeing chunk1: %s\n", chunk2);
    
    // Free chunk2
    free(chunk2);
    chunk2 = NULL;
    
    return 0;
}