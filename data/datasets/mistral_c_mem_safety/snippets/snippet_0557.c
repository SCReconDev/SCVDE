#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10

void copy_buffer(char *dest, const char *src, size_t size) {
    if (size <= BUFFER_SIZE) {
        strncpy(dest, src, size);
        dest[size] = '\0';
    } else {
        printf("Size exceeds buffer capacity.\n");
    }
}

int main() {
    char dest[BUFFER_SIZE];
    char src[] = "Hello, World!";
    copy_buffer(dest, src, strlen(src));
    printf("Copied string: %s\n", dest);
    return 0;
}