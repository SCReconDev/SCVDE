#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void handle_input(char* input) {
    char buffer[MAX_INPUT_SIZE];
    if (strlen(input) >= MAX_INPUT_SIZE) {
        printf("Input too large\n");
        return;
    }
    strcpy(buffer, input);
    printf("Input: %s\n", buffer);
}

int main() {
    char input[MAX_INPUT_SIZE];
    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);
    handle_input(input);
    return 0;
}