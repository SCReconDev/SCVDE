#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void handle_input() {
    char input[MAX_INPUT_SIZE];
    char buffer[MAX_INPUT_SIZE];

    printf("Enter your input: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        perror("Error reading input");
        return;
    }

    size_t input_len = strlen(input);
    if (input_len >= MAX_INPUT_SIZE) {
        fprintf(stderr, "Input too long\n");
        return;
    }

    memcpy(buffer, input, input_len);
    buffer[input_len] = '\0';

    printf("Processed input: %s\n", buffer);
}

int main() {
    handle_input();
    return 0;
}