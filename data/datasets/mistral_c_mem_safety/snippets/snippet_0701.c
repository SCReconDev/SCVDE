#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

void handleInput(char *input) {
    char buffer[BUFFER_SIZE];
    if (strlen(input) >= BUFFER_SIZE) {
        printf("Input too long\n");
        return;
    }
    strcpy(buffer, input);
    printf("Input handled: %s\n", buffer);
}

int main() {
    char userInput[BUFFER_SIZE];
    printf("Enter input: ");
    fgets(userInput, BUFFER_SIZE, stdin);
    userInput[strcspn(userInput, "\n")] = '\0';
    handleInput(userInput);
    return 0;
}