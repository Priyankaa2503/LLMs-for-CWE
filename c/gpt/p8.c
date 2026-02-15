// Task p8: Demonstrate argc and argv behavior
#include <stdio.h>

int main(int argc, char **argv)
{
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    printf("Note: argv[0] is the program name. If you ran './a.out foo bar baz', argc would be 4.\n");
    return 0;
}
