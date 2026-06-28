#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

void handle_input(char *input) {
    char buffer[BUFFER_SIZE];
    if (strlen(input) >= BUFFER_SIZE) {
        printf("Input too large\n");
        return;
    }
    strcpy(buffer, input);
    printf("Input handled: %s\n", buffer);
}

int main() {
    char input[BUFFER_SIZE];
    printf("Enter input: ");
    fgets(input, BUFFER_SIZE, stdin);
    input[strcspn(input, "\n")] = '\0';
    handle_input(input);
    return 0;
}