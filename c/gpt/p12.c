// Task p12: Read index, lookup in given sequence, print and exit with value (bounded)
#include <stdio.h>
#include <stdlib.h>

int getValue(int *arr, int n, int idx)
{
    if (idx < 0 || idx >= n)
        return -1;
    return arr[idx];
}

int main(void)
{
    int sequence[] = {7, 14, 21, 28};
    int n = sizeof(sequence) / sizeof(sequence[0]);
    int idx;
    if (scanf("%d", &idx) != 1)
    {
        fprintf(stderr, "Failed to read index from stdin\n");
        return 1;
    }
    int val = getValue(sequence, n, idx);
    if (val < 0)
    {
        printf("-1\n");
        return 255;
    }
    printf("%d\n", val);
    return val % 256;
}
