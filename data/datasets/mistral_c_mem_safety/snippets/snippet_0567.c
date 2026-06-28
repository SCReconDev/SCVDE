#include <stdio.h>
#include <string.h>

void copy_buffer(char* dest, const char* src, size_t size) {
    if (strlen(src) < size) {
        strcpy(dest, src);
    } else {
        printf("Source string too long.\n");
    }
}

int main() {
    char src[] = "Hello, world!";
    char dest[20];
    copy_buffer(dest, src, sizeof(dest));
    printf("Copied string: %s\n", dest);
    return 0;
}