#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

void handle_input(char *input) {
    char buffer[BUFFER_SIZE];
    size_t input_length = strlen(input);

    if (input_length >= BUFFER_SIZE) {
        printf("Input too long\n");
        return;
    }

    strncpy(buffer, input, BUFFER_SIZE - 1);
    buffer[BUFFER_SIZE - 1] = '\0';

    printf("Input handled: %s\n", buffer);
}

int main() {
    char *input = "Hello, World!";
    handle_input(input);

    return 0;
}