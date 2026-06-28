#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_input(char *input) {
    char buffer[BUFFER_SIZE];
    size_t input_len = strlen(input);

    if (input_len >= BUFFER_SIZE) {
        fprintf(stderr, "Input too long\n");
        return;
    }

    strncpy(buffer, input, BUFFER_SIZE - 1);
    buffer[BUFFER_SIZE - 1] = '\0';

    printf("Input: %s\n", buffer);
}

int main() {
    char input[BUFFER_SIZE];
    printf("Enter input: ");
    fgets(input, BUFFER_SIZE, stdin);

    handle_input(input);

    return 0;
}