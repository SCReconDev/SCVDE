#include <stdio.h>
#include <string.h>

void copy_buffer(char *src, char *dest, int size) {
    if (strlen(src) < size) {
        strcpy(dest, src);
    } else {
        printf("Source string too long\n");
    }
}

int main() {
    char src[50] = "Hello, World!";
    char dest[50];
    copy_buffer(src, dest, 50);
    printf("Copied string: %s\n", dest);
    return 0;
}