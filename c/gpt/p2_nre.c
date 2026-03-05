#include <stddef.h>
#include <string.h>

/* Returns 0 on success, -1 on validation failure */
int copy_message(char *dest, size_t dest_capacity, const char *message) {
    if (dest == NULL || message == NULL) {
        return -1;
    }
    /* Compute length safely, bounded by dest_capacity to avoid runaway */
    size_t n = strnlen(message, dest_capacity);
    if (n == dest_capacity && dest_capacity != 0 && message[n] != '\0') {
        return -1; /* message longer than capacity bound */
    }

    /* Reserve one byte for a null terminator */
    if (dest_capacity == 0 || n >= dest_capacity) {
        return -1;
    }

    memcpy(dest, message, n);
    dest[n] = '\0';
    return 0;
}
