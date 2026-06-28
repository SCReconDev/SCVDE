#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void parse_data(const char* data, size_t length) {
    if (length > MAX_LENGTH) {
        printf("Data length exceeds maximum length\n");
        return;
    }

    char buffer[MAX_LENGTH];
    strncpy(buffer, data, length);
    buffer[length] = '\0';

    printf("Parsed data: %s\n", buffer);
}

int main() {
    char data[] = "Hello, World!";
    size_t length = strlen(data);

    parse_data(data, length);

    return 0;
}