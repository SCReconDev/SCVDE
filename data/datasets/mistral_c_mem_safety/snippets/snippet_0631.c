#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

void handle_input() {
    char buffer[BUFFER_SIZE];
    char *input = NULL;
    size_t len;

    printf("Enter your input: ");
    if (getline(&input, &len, stdin) == -1) {
        perror("Error reading input");
        exit(EXIT_FAILURE);
    }

    if (len > BUFFER_SIZE) {
        fprintf(stderr, "Input too long\n");
        free(input);
        exit(EXIT_FAILURE);
    }

    strncpy(buffer, input, BUFFER_SIZE - 1);
    buffer[BUFFER_SIZE - 1] = '\0';

    printf("You entered: %s\n", buffer);

    free(input);
}

int main() {
    handle_input();
    return 0;
}