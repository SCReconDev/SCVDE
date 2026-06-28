#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10

void copy_buffer(char *source, char *destination, size_t size) {
    if (size > BUFFER_SIZE) {
        printf("Size mismatch\n");
        return;
    }

    memcpy(destination, source, size);
}

int main() {
    char source[BUFFER_SIZE] = "Hello";
    char destination[BUFFER_SIZE];

    copy_buffer(source, destination, strlen(source) + 1);
    printf("Destination: %s\n", destination);

    return 0;
}