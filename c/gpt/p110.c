#include <stdio.h>
#include <stdlib.h>

/* p110.c
   Run `id <username>` and print the exit status.
*/
int main(int argc, char **argv){
    if (argc < 2) { fprintf(stderr, "usage: %s username\n", argv[0]); return 1; }
    char cmd[256]; snprintf(cmd,sizeof(cmd), "id %s", argv[1]);
    int rc = system(cmd);
    if (rc == -1) { perror("system"); return 1; }
    int exit_status = WEXITSTATUS(rc);
    printf("exit status: %d\n", exit_status);
    return exit_status;
}
