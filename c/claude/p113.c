#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* p113.c - ping with status check */
int main(void) {
    char url[] = "example.com";
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ping -c 1 %s 2>&1", url);
    int status = system(cmd);
    if (status == 0) {
        printf("URL %s is alive\n", url);
    } else {
        printf("URL %s is not alive\n", url);
    }
    return 0;
}
