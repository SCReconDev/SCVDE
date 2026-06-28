#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

void handle_input(char *input) {
    char buffer[BUFFER_SIZE];
    if (strlen(input) < BUFFER_SIZE) {
        strcpy(buffer, input);
        printf("Input handled: %s\n", buffer);
    } else {
        printf("Input too long\n");
    }
}

int main() {
    char *input = "Hello, World!";
    handle_input(input);
    return 0;
}