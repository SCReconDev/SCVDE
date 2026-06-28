#include <stdio.h>
#include <string.h>

void parse_data(const char* data, int length) {
    char buffer[10];
    if (length > 10) {
        length = 10;
    }
    strncpy(buffer, data, length);
    printf("Parsed data: %s\n", buffer);
}

int main() {
    char data[20] = "Hello, World!";
    parse_data(data, 20);
    return 0;
}