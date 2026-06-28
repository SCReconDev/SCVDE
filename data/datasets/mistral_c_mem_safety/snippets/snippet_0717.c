#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_data(char *dest, const char *src, size_t size) {
    if (dest == NULL || src == NULL) {
        fprintf(stderr, "Null pointer\n");
        return;
    }

    if (strlen(src) >= size) {
        fprintf(stderr, "Source string too large\n");
        return;
    }

    strncpy(dest, src, size);
    dest[size - 1] = '\0';
}

int main() {
    char src[] = "Hello, world!";
    char dest[20];

    copy_data(dest, src, sizeof(dest));
    printf("Copied data: %s\n", dest);

    return 0;
}