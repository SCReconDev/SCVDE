#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_input(char *input) {
    char buffer[10];
    strcpy(buffer, input);
    printf("Input: %s\n", buffer);
}

int main() {
    char *input = "This is a very long input string that will cause a buffer overflow";
    handle_input(input);
    return 0;
}