#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_buffer(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL) {
        printf("Null pointer\n");
        return;
    }

    size_t src_len = strlen(src);

    if (src_len >= dest_size) {
        printf("Buffer overflow\n");
        return;
    }

    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
}

int main() {
    char dest[100];
    const char *src = "This is a test string";
    copy_buffer(dest, src, sizeof(dest));
    printf("Copied string: %s\n", dest);
    return 0;
}