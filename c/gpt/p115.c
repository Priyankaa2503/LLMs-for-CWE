#include <stdio.h>
#include <stdlib.h>

/* p115.c
   Use a helper function to execute ls command.
*/
int run_ls(void){
    return system("ls -la");
}
int main(void){
    int rc = run_ls();
    if (rc == -1) { perror("system"); return 1; }
    printf("exit code: %d\n", WEXITSTATUS(rc));
    return 0;
}
