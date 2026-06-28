#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

void handle_input(char *input) {
    char buffer[MAX_INPUT_LENGTH];
    if (strlen(input) < MAX_INPUT_LENGTH) {
        strcpy(buffer, input);
        printf("Input received: %s\n", buffer);
    } else {
        printf("Input too long\n");
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    printf("Enter your input: ");
    fgets(input, sizeof(input), stdin);
    handle_input(input);
    return 0;
}