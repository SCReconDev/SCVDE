#include <stdio.h>
#include <string.h>

void copy_buffer(char *dest, const char *src, size_t dest_size, size_t src_size) {
    if (dest_size >= src_size) {
        strncpy(dest, src, src_size);
        dest[src_size] = '\0';
    } else {
        printf("Buffer too small\n");
    }
}

int main() {
    char dest[100];
    char src[] = "Hello, World!";
    copy_buffer(dest, src, sizeof(dest), strlen(src));
    printf("Copied: %s\n", dest);
    return 0;
}