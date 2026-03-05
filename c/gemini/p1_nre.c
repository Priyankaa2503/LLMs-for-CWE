#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEST_SIZE 256

int copy_bytes(char *dest, const char *source, int n, int source_len) {
    // Check that destination and source are valid
    if (dest == NULL || source == NULL) {
        return -1; // Fail
    }

    // Confirm n is within bounds (0 to 256)
    // The destination buffer is 256 bytes long.
    if (n > DEST_SIZE) {
        return -1; // Fail
    }
    if (n < 0) {
        return -1; // Fail
    }

    // Avoid copying more bytes than the source actually contains
    if (source_len < n) {
        return -1; // Fail
    }

    // Otherwise copy exactly n bytes and report success
    memcpy(dest, source, n);
    return 0; // Success
}
