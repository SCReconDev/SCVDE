#include <stdio.h>
#include <string.h>

void handle_input(char *input) {
    char buffer[10];
    strcpy(buffer, input);
    printf("Input handled: %s\n", buffer);
}

int main() {
    char user_input[20] = "This is a long input";
    handle_input(user_input);
    return 0;
}