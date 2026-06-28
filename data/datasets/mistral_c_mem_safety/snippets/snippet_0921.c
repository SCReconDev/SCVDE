#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void handle_input(char *input) {
    char buffer[MAX_INPUT_SIZE];
    if (strlen(input) >= MAX_INPUT_SIZE) {
        printf("Input too large\n");
        return;
    }
    strcpy(buffer, input);
    printf("Input handled: %s\n", buffer);
}

int main() {
    char input[MAX_INPUT_SIZE];
    printf("Enter input: ");
    fgets(input, MAX_INPUT_SIZE, stdin);
    handle_input(input);
    return 0;
}