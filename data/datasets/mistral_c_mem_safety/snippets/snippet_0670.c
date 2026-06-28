#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_data(char *data, size_t length) {
    if (length < 1 || length > 1024) {
        printf("Invalid data length\n");
        return;
    }

    printf("Parsed data: %.*s\n", (int)length, data);
}

int main() {
    char data[] = "Hello, World!";
    size_t length = strlen(data);

    parse_data(data, length);

    return 0;
}