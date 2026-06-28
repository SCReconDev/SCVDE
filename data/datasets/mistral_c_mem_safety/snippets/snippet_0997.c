#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10

void copy_buffer(const char* src, char* dest, size_t dest_size) {
    if (strlen(src) >= dest_size) {
        printf("Buffer overflow\n");
        return;
    }

    strcpy(dest, src);
}

int main() {
    char src[] = "Hello, World!";
    char dest[BUFFER_SIZE];

    copy_buffer(src, dest, sizeof(dest));

    printf("Copied buffer: %s\n", dest);

    return 0;
}