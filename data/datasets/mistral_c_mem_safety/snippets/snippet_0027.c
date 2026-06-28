#include <stdio.h>
#include <string.h>

void copyData(char* dest, char* src, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

int main() {
    char source[20] = "Hello, World!";
    char destination[10];
    copyData(destination, source, 20);
    printf("Copied data: %s\n", destination);
    return 0;
}