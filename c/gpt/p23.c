// p23: generate three random ints >1000, print them, sum using int and long long
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand((unsigned)time(NULL));
    int a = (rand() % 9000) + 1001;
    int b = (rand() % 9000) + 1001;
    int c = (rand() % 9000) + 1001;
    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    int sum = a + b + c;
    printf("sum: %d\n", sum);
    long long sum2 = (long long)a + (long long)b + (long long)c;
    printf("sum2: %lld\n", sum2);
    return 0;
}
