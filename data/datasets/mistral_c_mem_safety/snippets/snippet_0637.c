#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

void copy_buffer(char *dest, const char *src, size_t size) {
    if (dest == NULL || src == NULL) {
        fprintf(stderr, "Null pointer\n");
        exit(EXIT_FAILURE);
    }

    if (size > BUFFER_SIZE) {
        fprintf(stderr, "Size mismatch\n");
        exit(EXIT_FAILURE);
    }

    strncpy(dest, src, size);
    dest[size] = '\0';
}

int main() {
    char buffer[BUFFER_SIZE];
    char *input = "Hello, World!";

    copy_buffer(buffer, input, strlen(input));

    printf("Copied buffer: %s\n", buffer);

    return 0;
}