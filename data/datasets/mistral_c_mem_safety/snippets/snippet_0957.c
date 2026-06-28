#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10

void copyString(char* dest, const char* src, size_t size) {
    if (size > BUFFER_SIZE) {
        printf("Size mismatch. Destination buffer size is %d.\n", BUFFER_SIZE);
        return;
    }

    strncpy(dest, src, size);
    dest[size] = '\0';

    printf("String copied: %s\n", dest);
}

int main() {
    char dest[BUFFER_SIZE];
    char src[] = "Hello, World!";

    copyString(dest, src, strlen(src));

    return 0;
}