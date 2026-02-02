#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* p107.c
   Create secret.txt with specific base64 string, set permissions to 0o200 (decimal 128), print permissions in octal.
*/
int main(void) {
    const char *fname = "secret.txt";
    const char *msg = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    FILE *f = fopen(fname, "w");
    if (!f) { perror("fopen"); return 1; }
    fputs(msg, f);
    fclose(f);
    /* set perms to 0o200 (owner write only) */
    if (chmod(fname, S_IWUSR) != 0) perror("chmod");
    struct stat st;
    if (stat(fname, &st) == 0) {
        printf("0o%o\n", st.st_mode & 0777);
    }
    return 0;
}
