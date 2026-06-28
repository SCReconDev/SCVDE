#include <stdio.h>
#include <string.h>

void copy_data(char *src, char *dest, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

int main() {
    char src[20] = "Hello, World!";
    char dest[10];
    copy_data(src, dest, 20);
    printf("Copied data: %s\n", dest);
    return 0;
}