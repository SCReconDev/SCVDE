#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void handle_input() {
    char input[MAX_INPUT_SIZE];
    char buffer[MAX_INPUT_SIZE];

    printf("Enter your input: ");
    fgets(input, sizeof(input), stdin);

    if (strlen(input) >= MAX_INPUT_SIZE) {
        printf("Input too long. Truncating...\n");
        input[MAX_INPUT_SIZE - 1] = '\0';
    }

    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    printf("Processed input: %s\n", buffer);
}

int main() {
    handle_input();
    return 0;
}