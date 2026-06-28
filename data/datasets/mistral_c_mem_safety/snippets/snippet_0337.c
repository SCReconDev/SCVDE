#include <stdio.h>
#include <string.h>

void copy_data(char *dest, char *src, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

int main() {
    char src[10] = "Hello";
    char dest[5];
    copy_data(dest, src, strlen(src));
    printf("Copied data: %s\n", dest);
    return 0;
}