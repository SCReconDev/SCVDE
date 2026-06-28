#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

void parse_input(const char *input, size_t length) {
    if (input == NULL) {
        fprintf(stderr, "Null input\n");
        exit(EXIT_FAILURE);
    }

    if (length > MAX_LENGTH) {
        fprintf(stderr, "Input too long\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < length; i++) {
        printf("%c", input[i]);
    }
    printf("\n");
}

int main() {
    char input[MAX_LENGTH + 1];
    size_t length;

    printf("Enter your input: ");
    fgets(input, sizeof(input), stdin);

    length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
        length--;
    }

    parse_input(input, length);

    return 0;
}