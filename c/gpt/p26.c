// p26: loop 3 times calling getMonthlySales(i) and sum for first quarter
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales(int i)
{
    return rand() % 100001;
}

int main(void)
{
    srand((unsigned)time(NULL));
    int sum = 0;
    for (int i = 0; i < 3; i++)
    {
        sum += getMonthlySales(i);
    }
    printf("Q1 total: %d\n", sum);
    return 0;
}
