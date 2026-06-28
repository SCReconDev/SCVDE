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
    char data[200] = "This is some data to parse";
    parse_data(data, 200);
    return 0;
}