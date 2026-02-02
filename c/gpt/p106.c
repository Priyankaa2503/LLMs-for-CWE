#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* p106.c
   Write a super-secret string to a file, set permissions to owner read-only (0400), print filename.
*/
int main(void) {
    const char *secret = "super secret info: do not share";
    const char *fname = "super_secret.txt";
    FILE *f = fopen(fname, "w");
    if (!f) { perror("fopen"); return 1; }
    fprintf(f, "%s\n", secret);
    fclose(f);
    if (chmod(fname, S_IRUSR) != 0) perror("chmod");
    printf("%s\n", fname);
    return 0;
}
