#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_buffer(char *src, char *dest, size_t size) {
    if (strlen(src) < size) {
        strcpy(dest, src);
    } else {
        printf("Source string too long\n");
    }
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];
    copy_buffer(src, dest, sizeof(dest));
    printf("Copied string: %s\n", dest);
    return 0;
}