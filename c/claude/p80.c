#include <stdio.h>
#include <string.h>

/* p80.c
   Read input using scanf with a scanset that stops at newline.
*/
int main(void) {
    char buf[1024];
    printf("Enter a string: ");
    // Read up to 1023 chars, stopping at newline; consume newline
    int n = scanf("%1023[^\n]%*c", buf);
    if (n > 0) {
        printf("Read %d char(s): %s\n", (int)strlen(buf), buf);
    }
    return 0;
}
