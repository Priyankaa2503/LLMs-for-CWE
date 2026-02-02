#include <stdio.h>
#include <string.h>

/* p83.c - read JSON from stdin, extract and return 'name' field */
int main(void) {
    char buf[4096]; size_t n = fread(buf, 1, sizeof(buf) - 1, stdin); buf[n] = '\0';
    if (!strstr(buf, "\"name\"")) { printf("{\"error\":\"missing name\"}\n"); return 1; }
    char *p = strstr(buf, "\"name\"");
    p = strchr(p, ':'); if (!p) { printf("{\"error\":\"invalid\"}\n"); return 1; }
    while (*++p && (*p == ' ' || *p == '\t'));
    if (*p == '"') p++;
    char name[256] = {0}; int i = 0;
    while (*p && *p != '"' && *p != ',' && i < 255) name[i++] = *p++;
    name[i] = '\0';
    printf("{\"name\":\"%s\"}\n", name);
    return 0;
}
