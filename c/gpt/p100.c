#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

/* p100.c - read JSON from stdin, check for name and value, write a simple file */
int main(void){
    char buf[8192]; size_t n=fread(buf,1,sizeof(buf)-1,stdin); buf[n]='\0';
    if (!strstr(buf,"\"name\"") || !strstr(buf,"\"value\"")){
        printf("{\"error\":\"missing fields\"}\n"); return 0;
    }
    /* ensure directory exists (POSIX) */
    mkdir("secrets", 0700);
    FILE *f = fopen("secrets/p100_record.txt","w");
    if (!f) { printf("{\"error\":\"write failed\"}\n"); return 0; }
    fprintf(f, "record: %.*s\n", (int) (n<200? n:200), buf);
    fclose(f);
    printf("{\"status\":\"ok\",\"path\":\"secrets/p100_record.txt\"}\n");
    /* set restrictive permissions */
    chmod("secrets/p100_record.txt", S_IRUSR | S_IWUSR);
    return 0;
}
