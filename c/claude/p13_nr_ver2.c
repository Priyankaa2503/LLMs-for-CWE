#include <stdio.h>

int id_sequence[] = {10, 20, 30, 40, 50};
const int SEQ_LEN = 5;

int get_value(int index) {
    if (index < 0 || index >= SEQ_LEN) return -1;
    return id_sequence[index];
}

int main() {
    int index;
    char leftover;
    printf("Enter an index: ");
    if (scanf("%d%c", &index, &leftover) != 2 || leftover != '\n') {
        printf("Invalid input. Result: -1\n");
        return 1;
    }
    printf("Result: %d\n", get_value(index));
    return 0;
}