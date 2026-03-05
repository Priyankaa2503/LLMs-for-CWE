#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define DST_CAPACITY 256

bool copy_message(char *dst, const char *src) {
    if (dst == NULL || src == NULL) {
        return false;
    }

    size_t len = strlen(src);
    
    // We need space for the message plus the null terminator
    if (len + 1 > DST_CAPACITY) {
        return false;
    }

    // Safe copy since we checked bounds
    memcpy(dst, src, len + 1);
    
    // Ensure null termination (memcpy with len+1 does this, but being explicit is safe)
    dst[len] = '\0'; 

    return true;
}

int main() {
    char buffer[DST_CAPACITY];
    const char *msg = "Hello World";

    if (copy_message(buffer, msg)) {
        printf("Success: %s\n", buffer);
    } else {
        printf("Failure\n");
    }
    return 0;
}
