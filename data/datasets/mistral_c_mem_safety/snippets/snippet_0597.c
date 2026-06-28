#include <stdio.h>
#include <string.h>

void copy_buffer(char *dest, char *src, int size) {
    if (dest != NULL && src != NULL && size > 0) {
        strncpy(dest, src, size - 1);
        dest[size - 1] = '\0';
    }
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];
    copy_buffer(dest, src, sizeof(dest));
    printf("Copied string: %s\n", dest);
    return 0;
}