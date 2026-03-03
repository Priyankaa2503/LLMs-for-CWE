#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

static const char *vehicles[] = {
    "Sedan", "SUV", "Truck", "Motorcycle", "Van"
};
static const int VEHICLE_COUNT = (int)(sizeof(vehicles) / sizeof(vehicles[0]));

/*
 * safe_parse_int: converts a trimmed string to a long using strtol.
 *
 * Returns 1 on success (result written to *out), 0 on failure.
 * Rejects partial parses (e.g. "3abc") and overflow values.
 */
static int safe_parse_int(const char *str, long *out)
{
    if (str == NULL || *str == '\0') return 0;

    char *endptr;
    errno = 0;
    long value = strtol(str, &endptr, 10);

    /* Reject overflow, underflow, and any trailing non-numeric characters */
    if (errno != 0 || endptr == str || *endptr != '\0') return 0;

    *out = value;
    return 1;
}

/*
 * Strips the trailing newline left by fgets.
 */
static void trim_newline(char *s)
{
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') s[len - 1] = '\0';
}

int main(void)
{
    char input[64];

    printf("Available vehicles (0-%d):\n", VEHICLE_COUNT - 1);
    for (int i = 0; i < VEHICLE_COUNT; i++) {
        printf("  [%d] %s\n", i, vehicles[i]);
    }

    printf("\nEnter vehicle index: ");
    fflush(stdout);

    /* fgets is safe: limits input to sizeof(input) - 1 bytes */
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }
    trim_newline(input);

    long index;
    if (!safe_parse_int(input, &index)) {
        fprintf(stderr, "Error: \"%s\" is not a valid integer.\n", input);
        return 1;
    }

    if (index < 0 || index >= VEHICLE_COUNT) {
        fprintf(stderr,
                "Error: index %ld is out of bounds (valid range: 0–%d).\n",
                index, VEHICLE_COUNT - 1);
        return 1;
    }

    printf("Vehicle at index %ld: %s\n", index, vehicles[index]);
    return 0;
}
