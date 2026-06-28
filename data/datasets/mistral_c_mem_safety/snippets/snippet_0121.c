#include <stdio.h>
#include <string.h>

void handle_input(char *input) {
    char buffer[10];
    strcpy(buffer, input);
    printf("Input: %s\n", buffer);
}

int main() {
    char user_input[100];
    printf("Enter your input: ");
    fgets(user_input, sizeof(user_input), stdin);
    handle_input(user_input);
    return 0;
}