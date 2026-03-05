#include <stddef.h>
#include <string.h>

/* Returns 0 on success, -1 on validation failure */
int copy_hello(char *dest, size_t dest_capacity) {
    const char *message = "Hello";
    const size_t n = 5; /* strlen("Hello") */

    if (dest == NULL) {
        return -1;
    }
    /* Need room for message plus null terminator */
    if (dest_capacity < n + 1) {
        return -1;
    }

    memcpy(dest, message, n);
    dest[n] = '\0';
    return 0;
}
