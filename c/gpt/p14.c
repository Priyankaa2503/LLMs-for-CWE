// p14: function prompts user for index, returns -1 if out of bounds; program returns 0
#include <stdio.h>

int getValuePrompt(void)
{
    int id_sequence[] = {10, 20, 30, 40};
    int n = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int idx;
    printf("Enter index: ");
    if (scanf("%d", &idx) != 1)
        return -1;
    if (idx < 0 || idx >= n)
        return -1;
    return id_sequence[idx];
}

int main(void)
{
    int val = getValuePrompt();
    printf("%d\n", val);
    return 0;
}
