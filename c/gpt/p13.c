// p13: prompt user for index, return value from id_sequence or -1 (printed)
#include <stdio.h>

int getValueAtIndex(int idx)
{
    int id_sequence[] = {100, 200, 300, 400};
    int n = sizeof(id_sequence) / sizeof(id_sequence[0]);
    if (idx < 0 || idx >= n)
        return -1;
    return id_sequence[idx];
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
    int val = getValueAtIndex(idx);
    printf("%d\n", val);
    return 0;
}
