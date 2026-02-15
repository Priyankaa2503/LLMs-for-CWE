// p15: function returns value if in bounds, else returns 0
#include <stdio.h>

int getValue(int idx)
{
    int id_sequence[] = {11, 22, 33, 44};
    int n = sizeof(id_sequence) / sizeof(id_sequence[0]);
    if (idx >= 0 && idx < n)
        return id_sequence[idx];
    return 0;
}

int main(void)
{
    int idx;
    printf("Index: ");
    if (scanf("%d", &idx) != 1)
    {
        printf("0\n");
        return 0;
    }
    printf("%d\n", getValue(idx));
    return 0;
}
