#include <stdio.h>
#include <string.h>

void copy_buffer(char *dest, const char *src, size_t dest_size) {
    if (strlen(src) >= dest_size) {
        fprintf(stderr, "Buffer overflow\n");
        return;
    }

    strcpy(dest, src);
}

int main() {
    char dest[10];
    const char *src = "Hello";
    copy_buffer(dest, src, sizeof(dest));
    printf("Copied string: %s\n", dest);
    return 0;
}