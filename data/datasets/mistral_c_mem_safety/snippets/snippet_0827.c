#include <stdio.h>
#include <string.h>

void copy_buffer(char *dest, char *src, int size) {
    if (strlen(src) >= size) {
        printf("Buffer overflow\n");
        return;
    }
    strcpy(dest, src);
}

int main() {
    char dest[10];
    char src[] = "Hello, World!";
    copy_buffer(dest, src, sizeof(dest));
    printf("Copied string: %s\n", dest);
    return 0;
}