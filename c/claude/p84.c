#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* p84.c - validate YAML type field (Create or Update) */
int main(void) {
    char buf[4096]; size_t n = fread(buf, 1, sizeof(buf) - 1, stdin); buf[n] = '\0';
    char *p = strstr(buf, "type"); int valid = 0;
    if (p) {
        p = strchr(p, ':'); if (p) {
            while (*++p && isspace(*p));
            if (strncmp(p, "Create", 6) == 0 || strncmp(p, "Update", 6) == 0) valid = 1;
        }
    }
    printf("{\"valid\":%s}\n", valid ? "true" : "false");
    return 0;
}
