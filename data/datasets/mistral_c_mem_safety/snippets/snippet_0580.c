#include <stdio.h>
#include <string.h>

void parse_data(const char* data, size_t length) {
    if (length > 0 && length <= 100) {
        char buffer[100];
        strncpy(buffer, data, length);
        buffer[length] = '\0';
        printf("Parsed data: %s\n", buffer);
    } else {
        printf("Invalid data length\n");
    }
}

int main() {
    char data[] = "Hello, World!";
    parse_data(data, strlen(data));
    return 0;
}