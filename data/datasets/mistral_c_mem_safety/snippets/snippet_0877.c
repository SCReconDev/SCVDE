#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_buffer(char *src, char *dest, size_t size) {
    if (size > strlen(src)) {
        printf("Size mismatch\n");
        return;
    }
    memcpy(dest, src, size);
    dest[size] = '\0';
    printf("Copied buffer: %s\n", dest);
}

int main() {
    char src[100] = "Hello, World!";
    char dest[100];
    size_t size;
    printf("Enter size: ");
    scanf("%zu", &size);
    copy_buffer(src, dest, size);
    return 0;
}