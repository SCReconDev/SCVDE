#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_input(char *input) {
    char buffer[BUFFER_SIZE];
    size_t input_length = strlen(input);

    if (input_length >= BUFFER_SIZE) {
        fprintf(stderr, "Input too long\n");
        exit(EXIT_FAILURE);
    }

    memcpy(buffer, input, input_length + 1);
    printf("Input handled: %s\n", buffer);
}

int main() {
    char *input = "Hello, World!";
    handle_input(input);
    return 0;
}