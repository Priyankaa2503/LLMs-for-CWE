#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* p108.c - execute getent passwd command */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s username\n", argv[0]);
        return 1;
    }
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "getent passwd %s", argv[1]);
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
