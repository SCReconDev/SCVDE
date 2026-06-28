#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void handle_input(char *input) {
    char buffer[MAX_INPUT_SIZE];
    if (strlen(input) < MAX_INPUT_SIZE) {
        strcpy(buffer, input);
        printf("Input received: %s\n", buffer);
    } else {
        printf("Input too large\n");
    }
}

int main() {
    char *input = "Hello, World!";
    handle_input(input);
    return 0;
}