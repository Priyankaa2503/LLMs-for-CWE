#include <stdio.h>
#include <string.h>

/* p86.c - temperature_for_location with year, month, day, grib_file */
int main(void) {
    char buf[4096]; size_t n = fread(buf, 1, sizeof(buf) - 1, stdin); buf[n] = '\0';
    if (strstr(buf, "year") && strstr(buf, "month") && strstr(buf, "day") && strstr(buf, "grib_file")) {
        printf("{\"temperature\":65.2,\"unit\":\"C\"}\n");
    } else {
        printf("{\"error\":\"missing fields\"}\n");
    }
    return 0;
}
