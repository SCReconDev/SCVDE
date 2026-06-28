#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

void copy_buffer(char *dest, char *src, size_t size) {
    if (size > BUFFER_SIZE) {
        printf("Size mismatch\n");
        return;
    }
    strncpy(dest, src, size);
    dest[size] = '\0';
}

int main() {
    char src[BUFFER_SIZE] = "Hello, World!";
    char dest[BUFFER_SIZE];
    copy_buffer(dest, src, strlen(src));
    printf("Copied string: %s\n", dest);
    return 0;
}