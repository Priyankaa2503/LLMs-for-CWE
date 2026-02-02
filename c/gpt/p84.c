#include <stdio.h>
#include <string.h>

/* Simple program that reads body from stdin (or query) and checks for YAML-like strings */
int main(void) {
    char buf[8192];
    size_t n = fread(buf, 1, sizeof(buf)-1, stdin);
    buf[n] = '\0';
    if (n == 0) {
        printf("Content-Type: application/json\n\n{\"error\": \"missing payload parameter\"}\n");
        return 0;
    }
    if (strstr(buf, "type: Create") || strstr(buf, "type: 'Create'") || strstr(buf, "type: \"Create\"")) {
        printf("Content-Type: application/json\n\n{\"error\": \"create not allowed\"}\n");
        return 0;
    }
    if ((strstr(buf, "type: Update") || strstr(buf, "type: 'Update'") || strstr(buf, "type: \"Update\"")) && strstr(buf, "name: UnsafeDeserialization")) {
        printf("Content-Type: application/json\n\n{\"error\": \"unsafe deserialization detected\"}\n");
        return 0;
    }
    printf("Content-Type: application/json\n\n{\"status\": \"ok\"}\n");
    return 0;
}
