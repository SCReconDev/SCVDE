#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

void copy_buffer(char *src, size_t src_size) {
    char buffer[BUFFER_SIZE];

    if (src_size > BUFFER_SIZE) {
        printf("Source buffer too large\n");
        return;
    }

    memcpy(buffer, src, src_size);
    printf("Buffer copied\n");
}

int main() {
    char src[] = "Hello, world!";
    copy_buffer(src, strlen(src) + 1);
    return 0;
}