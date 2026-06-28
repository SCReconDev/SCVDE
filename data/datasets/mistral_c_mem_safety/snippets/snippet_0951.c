#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

void handleInput(const char* input) {
    char buffer[BUFFER_SIZE];
    size_t inputLength = strlen(input);

    if (inputLength >= BUFFER_SIZE) {
        printf("Input too long. Maximum allowed length is %d.\n", BUFFER_SIZE - 1);
        return;
    }

    strncpy(buffer, input, BUFFER_SIZE - 1);
    buffer[BUFFER_SIZE - 1] = '\0';

    printf("Input handled: %s\n", buffer);
}

int main() {
    char input[BUFFER_SIZE];
    printf("Enter your input: ");
    fgets(input, sizeof(input), stdin);

    handleInput(input);

    return 0;
}