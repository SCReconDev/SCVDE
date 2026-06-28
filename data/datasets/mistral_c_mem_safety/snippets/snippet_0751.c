#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void processInput(char *input) {
    char buffer[MAX_INPUT_SIZE];
    if (strlen(input) < MAX_INPUT_SIZE) {
        strcpy(buffer, input);
        printf("Processed input: %s\n", buffer);
    } else {
        printf("Input too large.\n");
    }
}

int main() {
    char userInput[MAX_INPUT_SIZE];
    printf("Enter your input: ");
    fgets(userInput, sizeof(userInput), stdin);
    userInput[strcspn(userInput, "\n")] = '\0';
    processInput(userInput);
    return 0;
}