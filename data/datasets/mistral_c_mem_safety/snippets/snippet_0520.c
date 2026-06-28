#include <stdio.h>
#include <string.h>

void parse_data(const char* data, size_t length) {
    if (length > 0 && length <= 100) {
        char buffer[100];
        strncpy(buffer, data, length);
        buffer[length] = '\0';
        printf("Parsed: %s\n", buffer);
    } else {
        printf("Invalid length\n");
    }
}

int main() {
    char data[] = "Sample data";
    parse_data(data, strlen(data));
    return 0;
}