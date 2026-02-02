#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* p79.c
   Allocate two 1024-byte buffers and read up to 100 chars from stdin into each using fgets.
*/
int main(void) {
    char *buf = (char *)malloc(1024);
    char *buf1 = (char *)malloc(1024);
    if (!buf || !buf1) { perror("malloc"); return 1; }
    
    printf("Enter first line: ");
    if (fgets(buf, 101, stdin)) {
        printf("Read: %s\n", buf);
    }
    
    printf("Enter second line: ");
    if (fgets(buf1, 101, stdin)) {
        printf("Read: %s\n", buf1);
    }
    
    free(buf);
    free(buf1);
    return 0;
}
