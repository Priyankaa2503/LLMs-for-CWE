#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int copy_message(const char *source, char *dest, size_t dest_capacity) {
    if (source == NULL || dest == NULL) {
        return 0; // Failure: Null pointer
    }

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
    const char *msg1 = "Hello World";
    const char *msg2 = "This message is way too long for the buffer";

    // Valid call
    if (copy_message(msg1, dest, sizeof(dest))) {
        printf("Success: Copied '%s'\n", dest);
    } else {
        printf("Failure: Copy failed.\n");
    }

    // Invalid call (too long)
    if (copy_message(msg2, dest, sizeof(dest))) {
        printf("Success: Copied '%s'\n", dest);
    } else {
        printf("Failure: Copy rejected (too long).\n");
    }

    return 0;
}
