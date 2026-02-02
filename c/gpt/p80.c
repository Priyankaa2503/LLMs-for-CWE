#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[1024];

    /*
     * The format string reads up to 1023 characters that are not a newline
     * and then consumes the newline without storing it: "%1023[^\n]%*c"
     * scanf returns the number of items successfully assigned (1 on success).
     */
    printf("Enter a line (up to 1023 chars):\n");
    int ret = scanf("%1023[^\n]%*c", buf);

    if (ret == 1) {
        printf("scanf returned: %d\n", ret);
        printf("Stored string (length %zu): %s\n", strlen(buf), buf);
    } else if (ret == EOF) {
        printf("EOF reached or no input available.\n");
    } else {
        printf("No matching characters were read.\n");
    }

    return 0;
}
