#include <stdio.h>
#include <string.h>

void copy_string(char *dest, const char *src, size_t dest_size) {
    if (strlen(src) >= dest_size) {
        printf("Source string is too long\n");
        return;
    }
    strcpy(dest, src);
}

int main() {
    char dest[10];
    char src[] = "Hello";
    copy_string(dest, src, sizeof(dest));
    printf("Copied string: %s\n", dest);
    return 0;
}