#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_buffer(char *src, char *dest, size_t size) {
    if (strlen(src) < size) {
        strcpy(dest, src);
        printf("Buffer copied\n");
    } else {
        printf("Buffer too long\n");
    }
}

int main() {
    char src[100] = "Hello, World!";
    char dest[100];
    copy_buffer(src, dest, 100);
    printf("Destination: %s\n", dest);
    return 0;
}