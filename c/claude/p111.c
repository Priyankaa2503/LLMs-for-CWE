#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* p111.c - ping web endpoint */
int main(void) {
    char url[] = "example.com";
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ping -c 1 %s", url);
    system(cmd);
    return 0;
}
