#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_buffer(char *dest, const char *src, size_t dest_size) {
    size_t src_len = strlen(src);

    if (src_len >= dest_size) {
        fprintf(stderr, "Source buffer too large\n");
        return;
    }

    memcpy(dest, src, src_len);
    dest[src_len] = '\0';
}

int main() {
    char dest[20];
    const char *src = "Hello, World!";

    copy_buffer(dest, src, sizeof(dest));
    printf("Copied string: %s\n", dest);

    return 0;
}