#include <stdio.h>
#include <stdlib.h>

/* p115.c - execute ls using popen */
int main(int argc, char *argv[]) {
    char dir[256] = ".";
    if (argc > 1) {
        snprintf(dir, sizeof(dir), "%s", argv[1]);
    }
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "ls -la %s", dir);
    FILE *fp = popen(cmd, "r");
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            printf("%s", line);
        }
        pclose(fp);
    }
    return 0;
}
