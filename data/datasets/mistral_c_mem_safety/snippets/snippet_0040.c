#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length < 0 || length > 100) {
        printf("Invalid length\n");
        return;
    }
    char buffer[length];
    strncpy(buffer, data, length);
    printf("Parsed data: %s\n", buffer);
}

int main() {
    char *data = "This is a test string";
    parse_data(data, strlen(data) + 1);
    return 0;
}