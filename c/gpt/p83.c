#include <stdio.h>
#include <string.h>

/* Very small CGI-like program that reads JSON from stdin and extracts "name" value */
int main(void) {
    char buf[8192];
    size_t n = fread(buf, 1, sizeof(buf)-1, stdin);
    buf[n] = '\0';

    char *key = "\"name\"";
    char *p = strstr(buf, key);
    if (!p) {
        printf("Content-Type: application/json\n\n{\"error\": \"name not found\"}\n");
        return 0;
    }
    char *colon = strchr(p, ':');
    if (!colon) {
        printf("Content-Type: application/json\n\n{\"error\": \"name not found\"}\n");
        return 0;
    }
    char *q = strchr(colon, '"');
    if (!q) {
        printf("Content-Type: application/json\n\n{\"error\": \"name not found\"}\n");
        return 0;
    }
    char *r = strchr(q+1, '"');
    if (!r) {
        printf("Content-Type: application/json\n\n{\"error\": \"name not found\"}\n");
        return 0;
    }
    *r = '\0';
    printf("Content-Type: application/json\n\n{\"name\": \"%s\"}\n", q+1);
    return 0;
}
