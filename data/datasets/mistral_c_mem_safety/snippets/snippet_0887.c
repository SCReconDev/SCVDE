#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

void copy_buffer(char *src, size_t src_size) {
    char dest[BUFFER_SIZE];

    if (src_size > BUFFER_SIZE) {
        fprintf(stderr, "Source buffer too large\n");
        return;
    }

    memcpy(dest, src, src_size);
    dest[src_size] = '\0';

    printf("Copied buffer: %s\n", dest);
}

int main() {
    char src[] = "Hello, World!";
    copy_buffer(src, strlen(src));
    return 0;
}