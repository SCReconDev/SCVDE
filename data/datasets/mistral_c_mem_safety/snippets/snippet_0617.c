#include <stdio.h>
#include <string.h>

void safeBufferManipulation(char *dest, const char *src, size_t size) {
    if (size > 0) {
        strncpy(dest, src, size - 1);
        dest[size - 1] = '\0';
    }
}

int main() {
    char dest[10];
    const char *src = "Hello";
    safeBufferManipulation(dest, src, sizeof(dest));
    printf("Destination: %s\n", dest);
    return 0;
}