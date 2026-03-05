#include <stdio.h>
#include <string.h>

int copy_message(char *dest, const char *message, size_t dest_capacity) {
    // First check destination and source are valid
    if (dest == NULL || message == NULL) {
        return -1; // Fail
    }

    // Compute n = length(message) safely
    // strnlen is safer than strlen if we want to be paranoid, but strlen is standard for null-terminated
    size_t n = strlen(message);

    // Verify n is within the destination’s capacity
    // In C, account for the null terminator
    if (n + 1 > dest_capacity) {
        return -1; // Fail
    }

    // Otherwise copy exactly n bytes and report success
    // We copy n bytes plus the null terminator
    strncpy(dest, message, n);
    dest[n] = '\0'; // Ensure null termination
    
    return 0; // Success
}
