#include <stdio.h>
#include <stdlib.h>

/* p81.c
   Allocate a 1024-byte buffer and read up to 10 characters from stdin.
*/
int main(void) {
    char *buf = (char *)malloc(1024);
    if (!buf) { perror("malloc"); return 1; }
    
    printf("Enter up to 10 characters: ");
    if (fgets(buf, 11, stdin)) {
        printf("Read: %s\n", buf);
    }
    
    free(buf);
    return 0;
}
