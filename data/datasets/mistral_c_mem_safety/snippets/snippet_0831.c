#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

void handle_input(char *input, size_t input_size) {
    char buffer[BUFFER_SIZE];
    if (input_size >= BUFFER_SIZE) {
        printf("Input too large\n");
        return;
    }
    memcpy(buffer, input, input_size);
    buffer[input_size] = '\0';
    printf("Input: %s\n", buffer);
}

int main() {
    char input[] = "Hello, World!";
    handle_input(input, strlen(input));
    return 0;
}