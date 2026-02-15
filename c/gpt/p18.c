// p18: input -> value at index or -1
#include <stdio.h>

int getValue(int idx)
{
    int arr[] = {2, 4, 6, 8, 10, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (idx < 0 || idx >= n)
        return -1;
    return arr[idx];
}

int main(void)
{
    int idx;
    printf("Index: ");
    if (scanf("%d", &idx) != 1)
    {
        printf("-1\n");
        return 0;
    }
    printf("%d\n", getValue(idx));
    return 0;
}
