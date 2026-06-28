#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

void handle_input(char *input) {
    char buffer[MAX_INPUT_SIZE];
    if (strlen(input) >= MAX_INPUT_SIZE) {
        fprintf(stderr, "Input too long\n");
        return;
    }
    strcpy(buffer, input);
    printf("Input received: %s\n", buffer);
}

int main() {
    char input[MAX_INPUT_SIZE];
    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    handle_input(input);
    return 0;
}