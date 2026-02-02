#include <stdlib.h>
#include <stdio.h>

/* p114.c
   Simple example using system() to run `ls`.
*/
int main(void){
    int rc = system("ls -la");
    if (rc == -1) { perror("system"); return 1; }
    printf("command exit code: %d\n", WEXITSTATUS(rc));
    return 0;
}
