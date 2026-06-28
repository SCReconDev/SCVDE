#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void handle_input(char* input) {
    char buffer[MAX_INPUT_SIZE];
    size_t input_length = strlen(input);

    if (input_length >= MAX_INPUT_SIZE) {
        fprintf(stderr, "Input too large\n");
        return;
    }

    memcpy(buffer, input, input_length);
    buffer[input_length] = '\0';

    printf("Processed input: %s\n", buffer);
}

int main() {
    char input[MAX_INPUT_SIZE];
    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);

    handle_input(input);

    return 0;
}