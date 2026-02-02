#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* p109.c
   Read username from argv and search /etc/passwd for matching lines.
*/
int main(int argc, char **argv){
    if (argc < 2) { fprintf(stderr, "usage: %s username\n", argv[0]); return 1; }
    const char *user = argv[1];
    FILE *f = fopen("/etc/passwd","r");
    if (!f) { perror("fopen"); return 1; }
    char line[1024];
    while (fgets(line, sizeof(line), f)){
        if (strstr(line, user)) fputs(line, stdout);
    }
    fclose(f);
    return 0;
}
