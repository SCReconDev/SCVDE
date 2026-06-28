#include <stdio.h>
#include <stdlib.h>

void copy_buffer(char *src, char *dest, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

int main() {
    char src[10] = "123456789";
    char dest[5];
    copy_buffer(src, dest, 10);
    printf("Buffer copied\n");
    return 0;
}