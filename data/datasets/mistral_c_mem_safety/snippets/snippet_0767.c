#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

void copy_buffer(char* dest, const char* src, size_t size) {
    if (size > BUFFER_SIZE) {
        printf("Size exceeds buffer size\n");
        return;
    }

    strncpy(dest, src, size);
    dest[size] = '\0';

    printf("Buffer copied: %s\n", dest);
}

int main() {
    char dest[BUFFER_SIZE];
    char src[] = "Hello, World!";
    size_t size = strlen(src);

    copy_buffer(dest, src, size);

    return 0;
}