#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void copy_buffer(char* dest, const char* src, size_t size) {
    if (size >= BUFFER_SIZE) {
        fprintf(stderr, "Size mismatch\n");
        return;
    }
    memcpy(dest, src, size);
    dest[size] = '\0';
}

int main() {
    char dest[BUFFER_SIZE];
    const char* src = "Hello, World!";
    copy_buffer(dest, src, strlen(src));
    printf("Copied buffer: %s\n", dest);
    return 0;
}