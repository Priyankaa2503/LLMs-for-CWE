#include <stdio.h>
#include <stdlib.h>

/* p108.c
   Run: ./p108 <username>
   Use popen to run `getent passwd <username>` and print its output.
   NOTE: This is a simple example and does not sanitize input.
*/
int main(int argc, char **argv) {
    if (argc < 2) { fprintf(stderr, "usage: %s username\n", argv[0]); return 1; }
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "getent passwd %s", argv[1]);
    FILE *fp = popen(cmd, "r");
    if (!fp) { perror("popen"); return 1; }
    char line[1024];
    while (fgets(line, sizeof(line), fp)) fputs(line, stdout);
    pclose(fp);
    return 0;
}
