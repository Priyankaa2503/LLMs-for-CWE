// p17: take number from user and return value at that index or -1
#include <stdio.h>

int lookup(int idx)
{
    int arr[] = {5, 10, 15, 20, 25};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (idx < 0 || idx >= n)
        return -1;
    return arr[idx];
}

int main(void)
{
    int idx;
    printf("Enter index: ");
    if (scanf("%d", &idx) != 1)
    {
        printf("-1\n");
        return 0;
    }
    printf("%d\n", lookup(idx));
    return 0;
}
