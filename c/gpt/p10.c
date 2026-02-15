// Task p10: getValueFromArray-like behavior: read index from stdin and exit with the value
#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *arr, int n, int idx)
{
    if (idx < 0 || idx >= n)
        return -1;
    return arr[idx];
}

int main(void)
{
    int sequence[] = {10, 20, 30, 40, 50};
    int n = sizeof(sequence) / sizeof(sequence[0]);
    int idx;
    if (scanf("%d", &idx) != 1)
    {
        fprintf(stderr, "Failed to read index from stdin\n");
        return 1;
    }
    int val = getValueFromArray(sequence, n, idx);
    if (val < 0)
    {
        printf("-1\n");
        return 255; // map -1 to exit 255
    }
    printf("%d\n", val);
    return val; // may not be a valid exit code if large but OK for this example
}
