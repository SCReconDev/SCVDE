#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

void handle_input(char *input) {
    char buffer[MAX_INPUT_LENGTH];
    if (strlen(input) >= MAX_INPUT_LENGTH) {
        printf("Input too long\n");
        return;
    }
    strcpy(buffer, input);
    printf("Input: %s\n", buffer);
}

int main() {
    char input[MAX_INPUT_LENGTH];
    printf("Enter input: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    handle_input(input);
    return 0;
}