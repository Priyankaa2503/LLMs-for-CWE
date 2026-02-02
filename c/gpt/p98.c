#include <stdio.h>
#include <string.h>

/* p98.c - read stdin and respond with simple JSON summary
   Usage: echo '{"a":1}' | ./p98
*/
int main(void){
    char buf[8192];
    size_t n = fread(buf,1,sizeof(buf)-1,stdin);
    buf[n]='\0';
    /* naive check */
    int has_brace = strchr(buf,'{')!=NULL;
    printf("Content-Type: application/json\n\n");
    if(!has_brace){
        printf("{\"error\":\"invalid input\"}\n");
        return 0;
    }
    /* very small naive parser: count top-level keys by counting '"' pairs */
    int quotes=0; for(size_t i=0;i<n;i++) if(buf[i]=='\"') quotes++;
    int keys = quotes/2;
    printf("{\"status\":\"ok\",\"approx_keys\":%d}\n", keys);
    return 0;
}
