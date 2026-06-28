#include <stdio.h>
#include <string.h>

void processInput(char* input) {
    char buffer[10];
    strcpy(buffer, input);
    printf("Processed input: %s\n", buffer);
}

int main() {
    char userInput[100];
    printf("Enter your input: ");
    fgets(userInput, sizeof(userInput), stdin);
    processInput(userInput);
    return 0;
}