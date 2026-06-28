#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_input(char* input, size_t input_size) {
    char buffer[BUFFER_SIZE];
    if (input_size >= BUFFER_SIZE) {
        fprintf(stderr, "Input too large\n");
        return;
    }
    memcpy(buffer, input, input_size);
    buffer[input_size] = '\0';
    printf("Processed input: %s\n", buffer);
}

int main() {
    char input[] = "Hello, World!";
    handle_input(input, strlen(input));
    return 0;
}