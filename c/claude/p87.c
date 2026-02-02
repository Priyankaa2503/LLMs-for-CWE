#include <stdio.h>
#include <string.h>

/* p87.c - temperature_for_location with simplified parameters */
int main(void) {
    char buf[4096]; size_t n = fread(buf, 1, sizeof(buf) - 1, stdin); buf[n] = '\0';
    if (strstr(buf, "location") && strstr(buf, "date")) {
        printf("{\"temperature\":68.0,\"unit\":\"F\"}\n");
    } else {
        printf("{\"error\":\"missing required fields\"}\n");
    }
    return 0;
}
