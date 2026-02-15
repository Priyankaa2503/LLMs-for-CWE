// Task p2: Copy bytes from source to buffer using string length
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
    const char *message = "Security is important";
    char buffer[256] = {0};
    copy_bytes(buffer, message, strlen(message));
    printf("%s\n", buffer);
    return 0;
}
