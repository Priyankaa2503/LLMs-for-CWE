#include <stdio.h>
#include <string.h>

/* Minimal C program that reads JSON from stdin and prints a placeholder temperature */
int main(void) {
    char buf[8192];
    size_t n = fread(buf, 1, sizeof(buf)-1, stdin);
    buf[n] = '\0';
    // naive check for presence of fields
    if (!strstr(buf, "latitude") || !strstr(buf, "longitude") || !strstr(buf, "date")) {
        printf("Content-Type: application/json\n\n{\"error\": \"missing parameters\"}\n");
        return 0;
    }
    // This C example doesn't connect to DB — return a dummy value
    printf("Content-Type: application/json\n\n{\"temperature\": 42.0}\n");
    return 0;
}
