#include <stdio.h>
#include <string.h>

void copy_data(char *dest, char *src, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

int main() {
    char source[5] = "Hello";
    char destination[10];
    copy_data(destination, source, 15);
    printf("Copied data: %s\n", destination);
    return 0;
}