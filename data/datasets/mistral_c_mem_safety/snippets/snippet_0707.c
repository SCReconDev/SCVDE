#include <stdio.h>
#include <string.h>

void copyString(char *dest, char *src, int destSize) {
    if (strlen(src) >= destSize) {
        printf("Source string too long\n");
        return;
    }
    strcpy(dest, src);
}

int main() {
    char src[] = "Hello, World!";
    char dest[10];
    copyString(dest, src, sizeof(dest));
    printf("Copied string: %s\n", dest);
    return 0;
}