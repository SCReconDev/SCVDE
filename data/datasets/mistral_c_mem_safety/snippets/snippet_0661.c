#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

void handle_input(char *input) {
    char buffer[MAX_INPUT_SIZE];
    size_t input_len = strlen(input);

    if (input_len >= MAX_INPUT_SIZE) {
        printf("Input too large\n");
        return;
    }

    strncpy(buffer, input, input_len);
    buffer[input_len] = '\0';

    printf("Processed input: %s\n", buffer);
}

int main() {
    char *input = "Hello, World!";
    handle_input(input);

    return 0;
}