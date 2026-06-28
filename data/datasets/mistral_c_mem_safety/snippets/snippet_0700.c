#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void parse_input(char *input, size_t length) {
    if (length > MAX_LENGTH) {
        printf("Input too long\n");
        return;
    }

    if (length < 1) {
        printf("Input too short\n");
        return;
    }

    printf("Input parsed: %.*s\n", (int)length, input);
}

int main() {
    char input[] = "Hello, world!";
    parse_input(input, strlen(input));
    return 0;
}