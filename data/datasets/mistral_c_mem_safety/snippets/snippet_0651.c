#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

void handle_input(char *input) {
    char buffer[BUFFER_SIZE];
    size_t input_len = strlen(input);

    if (input_len >= BUFFER_SIZE) {
        fprintf(stderr, "Input too long\n");
        return;
    }

    memcpy(buffer, input, input_len);
    buffer[input_len] = '\0';

    printf("Processed input: %s\n", buffer);
}

int main() {
    char *input = "Hello, World!";
    handle_input(input);
    return 0;
}