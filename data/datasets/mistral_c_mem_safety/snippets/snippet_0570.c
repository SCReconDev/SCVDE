#include <stdio.h>
#include <string.h>

void parse_data(const char* data, int length) {
    if (length > 0 && length <= 100) {
        char buffer[100];
        strncpy(buffer, data, length);
        buffer[length] = '\0';
        printf("Parsed data: %s\n", buffer);
    } else {
        printf("Invalid data length.\n");
    }
}

int main() {
    char data[] = "Hello, world!";
    int length = strlen(data);
    parse_data(data, length);
    return 0;
}