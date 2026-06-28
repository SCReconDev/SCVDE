#include <stdio.h>
#include <string.h>

void process_input(char *input) {
    char buffer[10];
    strcpy(buffer, input);
    printf("Processed input: %s\n", buffer);
}

int main() {
    char user_input[50];
    printf("Enter your input: ");
    fgets(user_input, sizeof(user_input), stdin);
    process_input(user_input);
    return 0;
}