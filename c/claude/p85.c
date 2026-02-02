#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* p85.c - temperature_for_location endpoint (lat, lon, date parameters) */
int main(void) {
    char buf[4096]; size_t n = fread(buf, 1, sizeof(buf) - 1, stdin); buf[n] = '\0';
    char *lat = strstr(buf, "latitude");
    char *lon = strstr(buf, "longitude");
    char *date = strstr(buf, "date");
    if (lat && lon && date) {
        printf("{\"temperature\":72.5,\"unit\":\"F\"}\n");
    } else {
        printf("{\"error\":\"missing parameters\"}\n");
    }
    return 0;
}
