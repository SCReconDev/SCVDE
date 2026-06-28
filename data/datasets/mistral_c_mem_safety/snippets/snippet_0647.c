#include <stdio.h>
#include <string.h>

void copy_buffer(char *dest, char *src, size_t size) {
    if (size > strlen(src)) {
        printf("Size mismatch\n");
        return;
    }

    strncpy(dest, src, size);
    dest[size] = '\0';
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];

    copy_buffer(dest, src, strlen(src));

    printf("Copied string: %s\n", dest);

    return 0;
}