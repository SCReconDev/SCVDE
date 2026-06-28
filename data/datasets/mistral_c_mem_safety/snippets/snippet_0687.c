#include <stdio.h>
#include <string.h>

void copy_buffer(char *dest, char *src, int size) {
    if (strlen(src) < size) {
        strcpy(dest, src);
    } else {
        printf("Source string too large\n");
    }
}

int main() {
    char dest[100];
    char *src = "Hello, World!";
    copy_buffer(dest, src, sizeof(dest));
    printf("Copied string: %s\n", dest);
    return 0;
}