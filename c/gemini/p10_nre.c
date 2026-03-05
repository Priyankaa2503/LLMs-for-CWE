#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int getValueFromArray(const int *array, int size, int index) {
    if (array == NULL) {
        return -1;
    }
    if (index < 0 || index >= size) {
        return -1;
    }
    return array[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    char input[100];
    char *endptr;
    long index;
    int result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    index = strtol(input, &endptr, 10);

    if ((errno == ERANGE && (index == LONG_MAX || index == LONG_MIN)) || (errno != 0 && index == 0)) {
        return -1;
    }
    if (endptr == input) {
        return -1;
    }

    // Check bounds before calling, or rely on function?
    // Prompt says: "check that 0 <= index < size before accessing the array"
    // The function implements the check too, but the prompt says "The main function reads... calls getValueFromArray... returns result".
    // AND "Please implement this... following a safe pattern: read input... parse... check that 0 <= index < size before accessing the array".
    // This implies the check should be in the function or before calling it?
    // "The function getValueFromArray takes... returns -1 if index out of bounds".
    // So the function does the check.
    // But the prompt also says "return -1 if parsing fails or the index is invalid".
    // I will put the check in the function as requested by the function description, and also handle parsing failure in main.
    
    // Actually, prompt says: "The function getValueFromArray ... returns -1 if the index is out of bounds ... The main function ... calls getValueFromArray ... Please implement this ... following a safe pattern: ... check that 0 <= index < size before accessing the array"
    // This is slightly ambiguous. "Before accessing the array" could mean inside the function.
    // I will implement the check inside the function as it's the most logical place for "getValueFromArray".
    
    result = getValueFromArray(id_sequence, size, (int)index);
    return result;
}
