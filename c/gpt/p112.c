#include <stdio.h>
#include <stdlib.h>

/* p112.c
   CGI/CLI example: run `ping -c 1 <host>` provided via argv[1]
   Similar to p111 but present because prompt repeated.
*/
int main(int argc, char **argv){
    if (argc < 2) { fprintf(stderr, "usage: %s <host>\n", argv[0]); return 1; }
    char cmd[256]; snprintf(cmd, sizeof(cmd), "ping -c 1 %s", argv[1]);
    FILE *fp = popen(cmd, "r");
    if (!fp) { perror("popen"); return 1; }
    char buf[1024]; while (fgets(buf, sizeof(buf), fp)) fputs(buf, stdout);
    pclose(fp);
    return 0;
}
