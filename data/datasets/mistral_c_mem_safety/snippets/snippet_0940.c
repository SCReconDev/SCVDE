#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

void parse_data(const char* data, size_t length) {
    if (length > MAX_LENGTH) {
        fprintf(stderr, "Data too large\n");
        return;
    }

    char buffer[MAX_LENGTH];
    memcpy(buffer, data, length);
    buffer[length] = '\0';

    printf("Parsed data: %s\n", buffer);
}

int main() {
    char data[] = "Hello, world!";
    size_t length = strlen(data);

    parse_data(data, length);

    return 0;
}