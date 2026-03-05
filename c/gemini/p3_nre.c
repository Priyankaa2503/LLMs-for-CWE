#include <stdio.h>
#include <string.h>

int copy_hello(char *dest, const char *source, size_t dest_capacity) {
    // First check that destination and source are valid
    if (dest == NULL || source == NULL) {
        return -1; // Fail
    }

    // Compute n = length("Hello")
    // Assuming source is "Hello" as per prompt, or we use strlen(source)
    size_t n = strlen(source);

    // Verify that n does not exceed the destination capacity
    // In C, leave space for a null terminator if treating it as a C-string
    if (n + 1 > dest_capacity) {
        return -1; // Fail
    }

    // Otherwise copy exactly n bytes and report success
    strncpy(dest, source, n);
    dest[n] = '\0'; // Null terminate
    return 0; // Success
}
