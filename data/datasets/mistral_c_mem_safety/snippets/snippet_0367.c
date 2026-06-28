#include <stdio.h>
#include <string.h>

void copy_data(char *dest, char *src, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

int main() {
    char source[] = "This is a long string that will cause a buffer overflow";
    char destination[10];
    copy_data(destination, source, strlen(source));
    printf("Copied data: %s\n", destination);
    return 0;
}