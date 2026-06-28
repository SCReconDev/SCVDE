#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length > 0 && length < 100) {
        char buffer[length];
        strncpy(buffer, data, length);
        printf("Parsed data: %s\n", buffer);
    }
}

int main() {
    char input[50];
    printf("Enter your data: ");
    fgets(input, sizeof(input), stdin);
    parse_data(input, strlen(input));
    return 0;
}