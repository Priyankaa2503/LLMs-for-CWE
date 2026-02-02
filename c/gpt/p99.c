#include <stdio.h>
#include <string.h>

/* p99.c - read stdin JSON and check for numeric "id" key (very naive)
   Usage: echo '{"id":1}' | ./p99
*/
int main(void){
    char buf[8192]; size_t n = fread(buf,1,sizeof(buf)-1,stdin); buf[n]='\0';
    if (!strstr(buf, "\"id\"")){
        printf("{\"error\":\"missing id\"}\n");
        return 0;
    }
    /* try to find digits after id key (naive) */
    char *p = strstr(buf, "\"id\"");
    if (!p) { printf("{\"error\":\"missing id\"}\n"); return 0; }
    p = strchr(p, ':'); if (!p) { printf("{\"error\":\"invalid id\"}\n"); return 0; }
    /* skip spaces */
    while(*++p==' '||*p=='\t');
    /* print the rest until , or } */
    char out[64]; int i=0;
    while(*p && *p!=',' && *p!='}' && i+1<sizeof(out)) out[i++]=*p++;
    out[i]='\0';
    printf("{\"status\":\"ok\",\"id\":%s}\n", out);
    return 0;
}
