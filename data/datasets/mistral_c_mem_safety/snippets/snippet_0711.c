#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void handle_input(char *input) {
    char buffer[MAX_INPUT_SIZE];
    size_t input_len = strlen(input);

    if (input_len >= MAX_INPUT_SIZE) {
        fprintf(stderr, "Input too large\n");
        return;
    }

    strncpy(buffer, input, input_len);
    buffer[input_len] = '\0';

    printf("Processed input: %s\n", buffer);
}

int main() {
    char input[MAX_INPUT_SIZE];
    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);

    handle_input(input);

    return 0;
}