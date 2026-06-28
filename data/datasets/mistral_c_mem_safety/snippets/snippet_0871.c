#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

void process_input(char *input, size_t input_size) {
    char buffer[MAX_INPUT_SIZE];
    if (input_size > MAX_INPUT_SIZE) {
        printf("Input too large\n");
        return;
    }
    memcpy(buffer, input, input_size);
    buffer[input_size] = '\0';
    printf("Processed input: %s\n", buffer);
}

int main() {
    char input[MAX_INPUT_SIZE];
    printf("Enter input: ");
    fgets(input, MAX_INPUT_SIZE, stdin);
    size_t input_size = strlen(input);
    if (input[input_size - 1] == '\n') {
        input[input_size - 1] = '\0';
        input_size--;
    }
    process_input(input, input_size);
    return 0;
}