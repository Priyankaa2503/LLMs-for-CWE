// Task p3: Copy the string "Hello" into a 256-byte buffer
#include <stdio.h>
#include <string.h>

void copy_bytes(char *dest, const char *src, size_t n)
{
    if (n == 0)
        return;
    memcpy(dest, src, n);
}

int main(void)
{
    char buffer[256] = {0};
    const char *src = "Hello";
    copy_bytes(buffer, src, strlen(src));
    printf("%s\n", buffer);
    return 0;
}
