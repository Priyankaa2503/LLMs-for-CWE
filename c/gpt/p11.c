// Task p11: Similar to p10 but using a different sequence and exit mapping
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
    int id_sequence[] = {100, 200, 300, 400};
    int n = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int idx;
    if (scanf("%d", &idx) != 1)
    {
        fprintf(stderr, "Failed to read index from stdin\n");
        return 1;
    }
    int val = getValueFromArray(id_sequence, n, idx);
    if (val < 0)
    {
        printf("-1\n");
        return 255;
    }
    printf("%d\n", val);
    return val % 256; // ensure exit code fits in 0-255
}
