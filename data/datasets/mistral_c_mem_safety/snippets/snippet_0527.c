#include <stdio.h>
#include <string.h>

void copyString(char *dest, char *src, int size) {
    if (strlen(src) < size) {
        strcpy(dest, src);
    } else {
        printf("Source string too large\n");
    }
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];
    copyString(dest, src, sizeof(dest));
    printf("Copied string: %s\n", dest);
    return 0;
}