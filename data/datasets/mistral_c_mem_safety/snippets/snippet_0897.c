#include <stdio.h>
#include <string.h>

void copyString(char *dest, const char *src, size_t destSize) {
    if (dest == NULL || src == NULL) {
        printf("Null pointer provided.\n");
        return;
    }

    size_t srcLength = strlen(src);

    if (srcLength >= destSize) {
        printf("Destination buffer too small.\n");
        return;
    }

    strncpy(dest, src, destSize);
    dest[destSize - 1] = '\0';

    printf("Copied string: %s\n", dest);
}

int main() {
    char dest[10];
    const char *src = "Hello";

    copyString(dest, src, sizeof(dest));

    return 0;
}