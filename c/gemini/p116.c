#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[50];
    char *options = "-l";

    // 'sprintf' acts as the print function to format the string
    sprintf(command, "ls %s", options);

    // 'system' executes the command
    system(command);

    return 0;
}