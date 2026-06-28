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
    printf("Buffer copied\n");
}

int main() {
    char src[BUFFER_SIZE] = "Hello, World!";
    char dest[BUFFER_SIZE];
    int size = strlen(src);
    copy_buffer(src, dest, size);
    printf("Destination: %s\n", dest);
    return 0;
}