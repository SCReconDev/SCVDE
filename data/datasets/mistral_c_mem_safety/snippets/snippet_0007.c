#include <stdio.h>
#include <string.h>

void copy_buffer(char *src, char *dest, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

int main() {
    char src[10] = "Hello";
    char dest[5];
    copy_buffer(src, dest, 10);
    printf("Copied string: %s\n", dest);
    return 0;
}