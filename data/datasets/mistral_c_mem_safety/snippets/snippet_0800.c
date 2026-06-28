#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void parse_input(char *input, int length) {
    if (length > 0 && length <= MAX_LENGTH) {
        char buffer[MAX_LENGTH];
        strncpy(buffer, input, length);
        buffer[length] = '\0';
        printf("Parsed input: %s\n", buffer);
    } else {
        printf("Invalid length\n");
    }
}

int main() {
    char input[MAX_LENGTH] = "Hello, World!";
    parse_input(input, strlen(input));
    return 0;
}