#include <stdio.h>
#include <string.h>

void safeParserHelper(const char *input, size_t length) {
    if (length > 0 && length <= 100) {
        char buffer[101];
        strncpy(buffer, input, length);
        buffer[length] = '\0';
        printf("Parsed input: %s\n", buffer);
    } else {
        printf("Invalid input length\n");
    }
}

int main() {
    const char *input = "Hello, World!";
    size_t length = strlen(input);
    safeParserHelper(input, length);
    return 0;
}