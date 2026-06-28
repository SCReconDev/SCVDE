#include <stdio.h>
#include <string.h>

void copy_buffer() {
    char source[] = "Hello, world!";
    char destination[20];

    if (strlen(source) >= sizeof(destination)) {
        printf("Source string too long\n");
        return;
    }

    strcpy(destination, source);
    printf("Copied string: %s\n", destination);
}

int main() {
    copy_buffer();
    return 0;
}