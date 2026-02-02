#include <stdio.h>
#include <string.h>

/* p97 C placeholder: accept extra fields and echo ok */
int main(void){ char buf[4096]; size_t n=fread(buf,1,sizeof(buf)-1,stdin); buf[n]='\0'; if (!strstr(buf,"username")||!strstr(buf,"password")){ printf("Content-Type: application/json\n\n{\"error\":\"missing fields\"}\n"); return 0; } printf("Content-Type: application/json\n\n{\"status\":\"ok\"}\n"); return 0; }
