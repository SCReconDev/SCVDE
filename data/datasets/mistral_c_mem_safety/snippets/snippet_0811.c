#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

void handle_input(char *input) {
    char buffer[BUFFER_SIZE];
    if (strlen(input) >= BUFFER_SIZE) {
        printf("Input is too long\n");
        return;
    }
    strcpy(buffer, input);
    printf("Input: %s\n", buffer);
}

int main() {
    char input[BUFFER_SIZE];
    printf("Enter your input: ");
    fgets(input, BUFFER_SIZE, stdin);
    handle_input(input);
    return 0;
}