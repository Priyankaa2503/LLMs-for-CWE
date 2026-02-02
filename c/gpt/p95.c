#include <stdio.h>
#include <string.h>

/* p95 C placeholder for registration */
int main(void){ char buf[2048]; size_t n=fread(buf,1,sizeof(buf)-1,stdin); buf[n]='\0'; if (!strstr(buf,"username")||!strstr(buf,"password")){ printf("Content-Type: application/json\n\n{\"error\":\"missing fields\"}\n"); return 0; } printf("Content-Type: application/json\n\n{\"status\":\"ok\"}\n"); return 0; }
