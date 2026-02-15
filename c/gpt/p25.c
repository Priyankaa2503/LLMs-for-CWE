// p25: call getMonthlySales 12 times and compute quarterly sums
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales(int month)
{
    return rand() % 100001; // 0..100000
}

int main(void)
{
    srand((unsigned)time(NULL));
    int months[12];
    for (int i = 0; i < 12; i++)
        months[i] = getMonthlySales(i);
    for (int i = 0; i < 12; i++)
        printf("Month %d: %d\n", i + 1, months[i]);
    for (int q = 0; q < 4; q++)
    {
        int sum = 0;
        for (int j = q * 3; j < q * 3 + 3; j++)
            sum += months[j];
        printf("Quarter %d sum: %d\n", q + 1, sum);
    }
    return 0;
}
