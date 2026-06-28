#include <stdio.h>
#include <string.h>

void handle_input(char *input) {
    char buffer[10];
    strcpy(buffer, input);
    printf("Input received: %s\n", buffer);
}

int main() {
    char user_input[20] = "This is a long input string";
    handle_input(user_input);
    return 0;
}