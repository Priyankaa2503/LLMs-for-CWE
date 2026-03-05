#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEST_SIZE 256

int copy_bytes(const void *source, void *dest, size_t source_len, int n) {
    if (source == NULL || dest == NULL) {
        return 0; // Failure: Null pointer
    }
    if (n < 0) {
        return 0; // Failure: Negative count
    }
    if (n > DEST_SIZE) {
        return 0; // Failure: Exceeds destination size
    }
    if ((size_t)n > source_len) {
        return 0; // Failure: Exceeds source length
    }

    memcpy(dest, source, n);
    return 1; // Success
}

int main() {
    char source[] = "This is a test string for copying.";
    char dest[DEST_SIZE];
    
    // Valid call
    if (copy_bytes(source, dest, sizeof(source), 10)) {
        printf("Success: Copied 10 bytes.\n");
    } else {
        printf("Failure: Copy failed.\n");
    }

    // Invalid call (n too large)
    if (copy_bytes(source, dest, sizeof(source), 300)) {
        printf("Success: Copied 300 bytes.\n");
    } else {
        printf("Failure: Copy failed cleanly (n too large).\n");
    }

    return 0;
}
