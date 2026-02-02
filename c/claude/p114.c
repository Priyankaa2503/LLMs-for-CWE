#include <stdio.h>
#include <stdlib.h>

/* p114.c - execute ls command using system */
int main(int argc, char *argv[]) {
    char dir[256] = ".";
    if (argc > 1) {
        snprintf(dir, sizeof(dir), "%s", argv[1]);
    }
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "ls -la %s", dir);
    system(cmd);
    return 0;
}
