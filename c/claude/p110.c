#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* p110.c - execute id command and check exit status */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s username\n", argv[0]);
        return 1;
    }
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "id %s", argv[1]);
    int status = system(cmd);
    printf("Exit status: %d\n", status);
    return 0;
}
