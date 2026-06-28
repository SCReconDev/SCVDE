#include <stdio.h>
#include <string.h>

void copy_buffer(char *src, char *dest, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

int main() {
    char source[20] = "Hello, World!";
    char destination[10];
    copy_buffer(source, destination, 20);
    printf("Copied buffer: %s\n", destination);
    return 0;
}