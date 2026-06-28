#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

void copy_buffer(char *src, char *dest, int size) {
    if (size > BUFFER_SIZE) {
        printf("Size exceeds buffer capacity\n");
        return;
    }
    strncpy(dest, src, size);
    dest[size] = '\0';
}

int main() {
    char src[BUFFER_SIZE] = "Hello, World!";
    char dest[BUFFER_SIZE];
    copy_buffer(src, dest, strlen(src));
    printf("Copied buffer: %s\n", dest);
    return 0;
}