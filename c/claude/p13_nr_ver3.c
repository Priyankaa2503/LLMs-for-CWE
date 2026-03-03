#include <stdio.h>
#include <string.h>
#include <ctype.h>

int id_sequence[] = {10, 20, 30, 40, 50};
const int SEQ_LEN = 5;

int get_value(int index) {
    if (index < 0 || index >= SEQ_LEN) return -1;
    return id_sequence[index];
}

int main() {
    char buf[64];
    printf("Enter an index: ");

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        printf("Input error. Result: -1\n");
        return 1;
    }

    /* Reject if any non-digit/sign characters present */
    int i = 0;
    if (buf[0] == '-' || buf[0] == '+') i = 1;
    for (; buf[i] != '\0' && buf[i] != '\n'; i++) {
        if (!isdigit((unsigned char)buf[i])) {
            printf("Invalid input. Result: -1\n");
            return 1;
        }
    }

    int index;
    if (sscanf(buf, "%d", &index) != 1) {
        printf("Invalid input. Result: -1\n");
        return 1;
    }

    printf("Result: %d\n", get_value(index));
    return 0;
}