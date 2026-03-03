#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_CAPACITY 10

// Returns 0 on success, -1 on error
int safe_memcpy_string(char *dest, size_t dest_capacity,
                       const char *src) {
    if (dest == NULL || src == NULL) {
        fprintf(stderr, "Error: NULL pointer provided.\n");
        return -1;
    }

    size_t len = strnlen(src, dest_capacity); // safe strlen with cap
    if (len >= dest_capacity) {              // >= to leave room for '\0'
        fprintf(stderr, "Error: destination too small.\n");
        return -1;
    }

    memcpy(dest, src, len + 1);  // +1 copies the null terminator
    return 0;
}

int main(void) {
    char buffer[BUFFER_CAPACITY];
    const char *source = "Hello";

    if (safe_memcpy_string(buffer, BUFFER_CAPACITY, source) == 0)
        printf("Copied: %s\n", buffer);

    return 0;
}