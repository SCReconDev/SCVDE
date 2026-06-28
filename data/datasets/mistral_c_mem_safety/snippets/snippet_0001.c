#include <stdio.h>
#include <string.h>

void handle_input() {
    char buffer[10];
    char input[100];
    printf("Enter your name: ");
    fgets(input, sizeof(input), stdin);
    strcpy(buffer, input);
    printf("Hello, %s\n", buffer);
}

int main() {
    handle_input();
    return 0;
}