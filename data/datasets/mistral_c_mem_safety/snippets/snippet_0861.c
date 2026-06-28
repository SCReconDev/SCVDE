#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

void handle_input(char *input) {
    char buffer[BUFFER_SIZE];
    size_t input_len = strlen(input);

    if (input_len >= BUFFER_SIZE) {
        printf("Input too large\n");
        return;
    }

    strncpy(buffer, input, BUFFER_SIZE - 1);
    buffer[BUFFER_SIZE - 1] = '\0';

    printf("Input handled: %s\n", buffer);
}

int main() {
    char *input = "This is a test input";
    handle_input(input);
    return 0;
}