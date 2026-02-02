#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* p112.c - ping URL endpoint */
int main(void) {
    char url[] = "example.com";
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ping -c 1 %s 2>&1", url);
    FILE *output = popen(cmd, "r");
    if (output) {
        char line[256];
        while (fgets(line, sizeof(line), output)) {
            printf("%s", line);
        }
        pclose(output);
    }
    return 0;
}
