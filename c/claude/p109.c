#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* p109.c - grep username from /etc/passwd */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s username\n", argv[0]);
        return 1;
    }
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "cat /etc/passwd | grep %s", argv[1]);
    system(cmd);
    return 0;
}
