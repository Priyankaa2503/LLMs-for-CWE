#include <stdio.h>

int id_sequence[] = {10, 20, 30, 40, 50};
int sequence_length = 5;

int get_value(int index) {
    if (index < 0 || index >= sequence_length) return -1;
    return id_sequence[index];
}

int main() {
    int index;
    printf("Enter an index: ");
    if (scanf("%d", &index) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    printf("Result: %d\n", get_value(index));
    return 0;
}