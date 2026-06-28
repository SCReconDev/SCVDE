#include <stdio.h>
#include <string.h>

void copy_string(char *dest, char *src, int dest_size) {
    if (strlen(src) >= dest_size) {
        fprintf(stderr, "Destination buffer too small\n");
        return;
    }
    strcpy(dest, src);
}

int main() {
    char src[] = "Hello, world!";
    char dest[10];
    copy_string(dest, src, sizeof(dest));
    printf("Copied string: %s\n", dest);
    return 0;
}