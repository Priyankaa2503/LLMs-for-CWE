#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int copy_hello(char *dest, size_t dest_capacity) {
    if (dest == NULL) {
        return 0; // Failure: Null pointer
    }

    const char *source = "Hello";
    size_t len = strlen(source);

    if (len >= dest_capacity) {
        return 0; // Failure: Destination too small (need space for null terminator)
    }

    // Safe copy
    memcpy(dest, source, len);
    dest[len] = '\0'; // Ensure null termination

    return 1; // Success
}

int main() {
    char dest[20];
    char small_dest[3];

    // Valid call
    if (copy_hello(dest, sizeof(dest))) {
        printf("Success: Copied '%s'\n", dest);
    } else {
        printf("Failure: Copy failed.\n");
    }

    // Invalid call (too small)
    if (copy_hello(small_dest, sizeof(small_dest))) {
        printf("Success: Copied '%s'\n", small_dest);
    } else {
        printf("Failure: Copy rejected (buffer too small).\n");
    }

    return 0;
}
