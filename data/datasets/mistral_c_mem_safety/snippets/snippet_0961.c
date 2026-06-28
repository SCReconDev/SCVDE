#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void handle_input(char *input) {
    char buffer[MAX_INPUT_SIZE];
    size_t input_length = strlen(input);

    if (input_length >= MAX_INPUT_SIZE) {
        printf("Input too large\n");
        return;
    }

    strncpy(buffer, input, input_length);
    buffer[input_length] = '\0';

    printf("Processed input: %s\n", buffer);
}

int main() {
    char *input = "Hello, World!";
    handle_input(input);
    return 0;
}