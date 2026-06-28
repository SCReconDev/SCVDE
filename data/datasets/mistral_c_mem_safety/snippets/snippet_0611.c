#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

void safeInputHandler(char *input, size_t size) {
    char buffer[BUFFER_SIZE];
    if (size > BUFFER_SIZE - 1) {
        size = BUFFER_SIZE - 1;
    }
    strncpy(buffer, input, size);
    buffer[size] = '\0';
    printf("Input: %s\n", buffer);
}

int main() {
    char input[] = "Hello, World!";
    safeInputHandler(input, strlen(input));
    return 0;
}