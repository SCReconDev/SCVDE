#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void handle_input() {
    char input[MAX_INPUT_SIZE];
    printf("Enter your input: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        printf("You entered: %s\n", input);
    } else {
        printf("Error reading input.\n");
    }
}

int main() {
    handle_input();
    return 0;
}