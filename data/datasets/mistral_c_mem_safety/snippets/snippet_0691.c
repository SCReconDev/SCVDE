#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

void handle_input(char *input) {
    char buffer[BUFFER_SIZE];
    size_t input_length = strlen(input);

    if (input_length >= BUFFER_SIZE) {
        printf("Input too long\n");
        return;
    }

    strcpy(buffer, input);
    printf("Input handled: %s\n", buffer);
}

int main() {
    char input[BUFFER_SIZE];
    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);
    handle_input(input);
    return 0;
}