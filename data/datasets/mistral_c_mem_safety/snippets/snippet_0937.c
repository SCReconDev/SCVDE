#include <stdio.h>
#include <string.h>

void copy_buffer(char* dest, const char* src, size_t size) {
    if (size > strlen(src)) {
        fprintf(stderr, "Size mismatch\n");
        return;
    }

    memcpy(dest, src, size);
    dest[size] = '\0';
}

int main() {
    char src[] = "Hello, world!";
    char dest[20];

    copy_buffer(dest, src, strlen(src));

    printf("Copied string: %s\n", dest);

    return 0;
}