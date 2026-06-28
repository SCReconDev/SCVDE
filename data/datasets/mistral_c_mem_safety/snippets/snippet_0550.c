#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void parse_input(char *input, int length) {
    if (input != NULL && length > 0 && length <= MAX_LENGTH) {
        for (int i = 0; i < length; i++) {
            printf("Input[%d]: %c\n", i, input[i]);
        }
    } else {
        printf("Invalid input or length\n");
    }
}

int main() {
    char input[MAX_LENGTH] = "Hello, World!";
    int length = strlen(input);
    parse_input(input, length);
    return 0;
}