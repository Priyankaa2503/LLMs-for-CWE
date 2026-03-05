#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DST_CAPACITY 256

bool copy_n_bytes(void *dst, const void *src, int n) {
    if (dst == NULL || src == NULL) {
        return false;
    }
    
    if (n < 0 || n > DST_CAPACITY) {
        return false;
    }

    // In C, we can't easily check if src has at least n bytes without additional info.
    // However, the prompt asks to fail if we can determine it. 
    // Standard C pointers don't carry size info. 
    // We proceed assuming src is valid for n bytes if not null, as per standard C behavior,
    // but strictly check n against destination capacity.

    memcpy(dst, src, n);
    return true;
}

int main() {
    char src[] = "Hello, World!";
    char dst[DST_CAPACITY];
    
    // Example usage
    if (copy_n_bytes(dst, src, 5)) {
        printf("Copied successfully: %.*s\n", 5, dst);
    } else {
        printf("Copy failed\n");
    }

    return 0;
}
