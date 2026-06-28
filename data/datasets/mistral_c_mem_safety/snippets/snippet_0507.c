#include <stdio.h>
#include <string.h>

void copy_string(char* dest, const char* src, size_t dest_size) {
    if (strlen(src) < dest_size) {
        strcpy(dest, src);
        printf("String copied: %s\n", dest);
    } else {
        printf("Destination buffer too small\n");
    }
}

int main() {
    char dest[10];
    const char* src = "Hello, World!";
    copy_string(dest, src, sizeof(dest));
    return 0;
}