#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_buffer(char *src, char *dest, size_t size) {
    if (size > strlen(src)) {
        printf("Size mismatch\n");
        return;
    }

    strncpy(dest, src, size);
    dest[size] = '\0';

    printf("Buffer copied\n");
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];
    size_t size = strlen(src);

    copy_buffer(src, dest, size);

    return 0;
}