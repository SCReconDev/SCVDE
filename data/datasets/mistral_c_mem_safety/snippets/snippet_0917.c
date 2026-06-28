#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void copy_data(char *src, char *dest, size_t size) {
    if (size > BUFFER_SIZE) {
        fprintf(stderr, "Size exceeds buffer size\n");
        return;
    }

    strncpy(dest, src, size);
    dest[size] = '\0';
}

int main() {
    char src[BUFFER_SIZE];
    char dest[BUFFER_SIZE];
    size_t size;

    printf("Enter source string: ");
    fgets(src, BUFFER_SIZE, stdin);

    printf("Enter size: ");
    scanf("%zu", &size);

    copy_data(src, dest, size);

    printf("Copied data: %s\n", dest);

    return 0;
}