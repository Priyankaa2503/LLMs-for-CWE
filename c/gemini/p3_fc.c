#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define DST_CAPACITY 256

bool copy_hello(char *dst, const char *src, size_t n) {
    if (dst == NULL || src == NULL) {
        return false;
    }

    // Validate that n (derived from length) fits in destination
    // We need space for n bytes + null terminator
    if (n >= DST_CAPACITY) {
        return false;
    }

    // Copy exactly n bytes
    memcpy(dst, src, n);
    
    // Ensure null termination
    dst[n] = '\0';

    return true;
}

int main() {
    char buffer[DST_CAPACITY];
    const char *hello = "Hello";
    size_t len = strlen(hello);

    if (copy_hello(buffer, hello, len)) {
        printf("Copied: %s\n", buffer);
    } else {
        printf("Failed to copy\n");
    }

    return 0;
}
