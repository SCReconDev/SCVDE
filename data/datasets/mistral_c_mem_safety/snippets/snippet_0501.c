#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void handle_input(const char* input) {
    char buffer[MAX_INPUT_SIZE];
    if (strlen(input) < MAX_INPUT_SIZE) {
        strcpy(buffer, input);
        printf("Input handled: %s\n", buffer);
    } else {
        printf("Input too large\n");
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);
    handle_input(input);
    return 0;
}