#include <stdio.h>
#include <string.h>

void copy_buffer(char *src, char *dest, int size) {
    if (strlen(src) < size) {
        strcpy(dest, src);
        printf("Buffer copied successfully\n");
    } else {
        printf("Buffer size mismatch\n");
    }
}

int main() {
    char src[100] = "Hello, World!";
    char dest[100];
    copy_buffer(src, dest, sizeof(dest));
    printf("Copied buffer: %s\n", dest);
    return 0;
}