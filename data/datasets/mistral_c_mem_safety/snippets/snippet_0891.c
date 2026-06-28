#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void processInput(char *input) {
    char buffer[MAX_INPUT_SIZE];
    size_t inputLength = strlen(input);

    if (inputLength >= MAX_INPUT_SIZE) {
        printf("Input too large.\n");
        return;
    }

    strncpy(buffer, input, inputLength);
    buffer[inputLength] = '\0';

    printf("Processed input: %s\n", buffer);
}

int main() {
    char userInput[MAX_INPUT_SIZE];
    printf("Enter input: ");
    fgets(userInput, sizeof(userInput), stdin);

    processInput(userInput);

    return 0;
}