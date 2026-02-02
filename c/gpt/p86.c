#include <stdio.h>
#include <string.h>

/* C placeholder for p86: read JSON and respond with dummy max temperature */
int main(void) {
    char buf[8192];
    size_t n = fread(buf,1,sizeof(buf)-1,stdin);
    buf[n]='\0';
    if (!strstr(buf,"latitude")||!strstr(buf,"longitude")||!strstr(buf,"year")||!strstr(buf,"month")||!strstr(buf,"day")||!strstr(buf,"grib_file")){
        printf("Content-Type: application/json\n\n{\"error\": \"missing parameters\"}\n");
        return 0;
    }
    printf("Content-Type: application/json\n\n{\"max_temperature\": 55.5}\n");
    return 0;
}
