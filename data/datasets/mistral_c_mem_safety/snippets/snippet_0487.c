#include <stdio.h>
#include <string.h>

void copy_data(char *source, char *destination, int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

int main() {
    char source[10] = "Hello";
    char destination[5];
    copy_data(source, destination, 10);
    printf("Copied data: %s\n", destination);
    return 0;
}