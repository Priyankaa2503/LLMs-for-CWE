// Task p1: Copy n bytes from src to dest; dest buffer is 256 bytes
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
    char dest[256] = {0};
    const char *src = "Example message to copy into buffer.";
    copy_bytes(dest, src, strlen(src));
    printf("%s\n", dest);
    return 0;
}
