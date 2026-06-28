#include <stdio.h>
#include <string.h>

void copy_buffer(char* dest, const char* src, size_t dest_size) {
    if (dest_size <= strlen(src)) {
        fprintf(stderr, "Buffer too small\n");
        return;
    }

    memcpy(dest, src, dest_size);
}

int main() {
    char dest[10];
    const char* src = "Hello";

    copy_buffer(dest, src, sizeof(dest));

    printf("Copied string: %s\n", dest);

    return 0;
}