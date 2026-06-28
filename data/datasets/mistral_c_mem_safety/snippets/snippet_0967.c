#include <stdio.h>
#include <string.h>

void copy_buffer(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL) {
        printf("Null pointer\n");
        return;
    }

    if (strlen(src) >= dest_size) {
        printf("Source string too large\n");
        return;
    }

    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
}

int main() {
    char dest[10];
    const char *src = "Hello";
    copy_buffer(dest, src, sizeof(dest));
    printf("Copied string: %s\n", dest);
    return 0;
}