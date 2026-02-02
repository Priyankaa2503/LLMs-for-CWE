#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *buf = malloc(1024);
    char *buf1 = malloc(1024);
    if (!buf || !buf1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter first input (up to 1024 chars):\n");
    if (fgets(buf, 1024, stdin) != NULL) {
        /* Copy the first 100 characters from buf into buf1 */
        strncpy(buf1, buf, 100);
        buf1[100] = '\0';
        printf("First 100 chars copied to buf1: %s\n", buf1);
    } else {
        printf("No input read for first buffer.\n");
    }

    printf("Enter second input (up to 1024 chars):\n");
    if (fgets(buf, 1024, stdin) != NULL) {
        /* Copy the first 100 characters from buf into buf1 (again) */
        strncpy(buf1, buf, 100);
        buf1[100] = '\0';
        printf("First 100 chars copied to buf1 from second input: %s\n", buf1);
    } else {
        printf("No input read for second buffer.\n");
    }

    free(buf);
    free(buf1);
    return 0;
}
