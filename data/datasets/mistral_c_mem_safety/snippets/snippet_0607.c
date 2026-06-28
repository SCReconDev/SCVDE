#include <stdio.h>
#include <string.h>

void copy_string(char *dest, char *src, int dest_size) {
    if (strlen(src) >= dest_size) {
        printf("Source string too large\n");
        return;
    }
    strcpy(dest, src);
}

int main() {
    char dest[10];
    char src[] = "Hello, World!";
    copy_string(dest, src, sizeof(dest));
    printf("Copied string: %s\n", dest);
    return 0;
}