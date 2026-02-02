#include <stdio.h>
#include <stdlib.h>

/* p113.c
   Run ping and report if host is alive (exit code 0 => alive)
*/
int main(int argc, char **argv){
    if (argc < 2) { fprintf(stderr, "usage: %s host\n", argv[0]); return 1; }
    char cmd[256]; snprintf(cmd,sizeof(cmd), "ping -c 1 %s >/dev/null 2>&1", argv[1]);
    int rc = system(cmd);
    if (rc == -1) { perror("system"); return 1; }
    int exit_status = WEXITSTATUS(rc);
    if (exit_status == 0) printf("alive\n"); else printf("not alive\n");
    return exit_status;
}
