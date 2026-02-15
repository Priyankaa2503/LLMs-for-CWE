// p16: takes integer input, returns value at that index; -1 for -1 or out-of-bounds
#include <stdio.h>

int getByIndex(int idx)
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (idx == -1)
        return -1;
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
    printf("%d\n", getByIndex(idx));
    return 0;
}
