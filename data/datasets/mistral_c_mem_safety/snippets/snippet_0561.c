#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void handle_input(char* input) {
    char buffer[MAX_INPUT_SIZE];
    if (strlen(input) < MAX_INPUT_SIZE) {
        strcpy(buffer, input);
        printf("Input: %s\n", buffer);
    } else {
        printf("Input too long.\n");
    }
}

int main() {
    char user_input[MAX_INPUT_SIZE];
    printf("Enter your input: ");
    fgets(user_input, sizeof(user_input), stdin);
    user_input[strcspn(user_input, "\n")] = '\0';
    handle_input(user_input);
    return 0;
}