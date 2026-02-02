#include <stdio.h>
#include <string.h>

/* C placeholder for p87: read JSON and return dummy or found value */
int main(void){
    char buf[8192];
    size_t n=fread(buf,1,sizeof(buf)-1,stdin);
    buf[n]='\0';
    if (!strstr(buf,"latitude")||!strstr(buf,"longitude")||!strstr(buf,"date")){
        printf("Content-Type: application/json\n\n{\"error\": \"missing parameters\"}\n"); return 0;
    }
    printf("Content-Type: application/json\n\n{\"temperature\": 21.5}\n");
    return 0;
}
