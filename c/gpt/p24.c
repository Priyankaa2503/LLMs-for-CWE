// p24: generate two random ints 10..1000 and print difference
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand10to1000()
{
    return (rand() % 991) + 10; // 10..1000
}

int main(void)
{
    srand((unsigned)time(NULL));
    int a = rand10to1000();
    int b = rand10to1000();
    int diff = a - b;
    printf("a: %d\n", a);
    printf("b: %d\n", b);
    printf("difference: %d\n", diff);
    return 0;
}
