#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

void copy_string(char *dest, char *src, int size) {
    if (dest != NULL && src != NULL && size > 0) {
        strncpy(dest, src, size);
        dest[size - 1] = '\0';
    }
}

int main() {
    char src[BUFFER_SIZE] = "Hello, World!";
    char dest[BUFFER_SIZE];
    copy_string(dest, src, BUFFER_SIZE);
    printf("Copied string: %s\n", dest);
    return 0;
}