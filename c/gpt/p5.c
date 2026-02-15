// Task p5: Read command-line arg, convert to int and print vehicle or 'invalid input'
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    const char *vehicles[] = {"car", "truck", "motorcycle", "bicycle"};
    const int n = sizeof(vehicles) / sizeof(vehicles[0]);
    if (argc < 2)
    {
        printf("invalid input\n");
        return 0;
    }
    char *endptr;
    long idx = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0')
    {
        printf("invalid input\n");
        return 0;
    }
    if (idx < 0 || idx >= n)
    {
        printf("invalid input\n");
    }
    else
    {
        printf("%s\n", vehicles[idx]);
    }
    return 0;
}
