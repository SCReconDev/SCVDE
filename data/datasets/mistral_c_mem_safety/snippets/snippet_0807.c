#include <stdio.h>
#include <string.h>

void copy_buffer(char* dest, char* src, int size) {
    if (strlen(src) >= size) {
        printf("Source buffer too large\n");
        return;
    }
    strncpy(dest, src, size);
    printf("Buffer copied\n");
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];
    copy_buffer(dest, src, sizeof(dest));
    printf("Destination: %s\n", dest);
    return 0;
}