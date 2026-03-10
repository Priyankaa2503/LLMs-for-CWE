// C - Primary Reference Implementation (Secure)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_BUFFER_SIZE 256

int main(void) {
    const char *source = "Secure memory copy example";
    size_t source_len = strlen(source);
    
    // CWE-252: Check allocation failure
    if (source_len >= MAX_BUFFER_SIZE) {
        fprintf(stderr, "Error: Source too large (%zu >= %zu)\n", 
                source_len, MAX_BUFFER_SIZE);
        return EXIT_FAILURE;
    }
    
    char *buffer = (char *)malloc(MAX_BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    
    // CWE-120/121: Bounded copy with null terminator consideration
    // source_len + 1 accounts for null terminator
    if (memcpy(buffer, source, source_len + 1) == NULL) {
        fprintf(stderr, "Error: Memory copy failed\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    // Ensure null termination
    buffer[source_len] = '\0';
    
    // Print data
    printf("Buffer contents: %s\n", buffer);
    printf("Buffer length: %zu\n", strlen(buffer));
    
    // CWE-415/CWE-416: Free exactly once, avoid double-free and use-after-free
    free(buffer);
    buffer = NULL;  // Defensive programming
    
    return EXIT_SUCCESS;
}
