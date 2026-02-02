#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *buf = malloc(1024);
    if (!buf) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    printf("Enter input (up to 10 chars will be read):\n");
    /* fgets reads up to n-1 characters; here we pass 10 so it will read up to 9 chars plus NUL */
    if (fgets(buf, 10, stdin) != NULL) {
        printf("Read: %s\n", buf);
    } else {
        printf("No input read.\n");
    }

    free(buf);
    return 0;
}
