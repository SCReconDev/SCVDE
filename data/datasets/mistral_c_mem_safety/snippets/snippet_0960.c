#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void parseData(const char* data, size_t length) {
    if (length > MAX_LENGTH) {
        printf("Data length exceeds maximum allowed length of %d.\n", MAX_LENGTH);
        return;
    }

    char buffer[MAX_LENGTH + 1];
    strncpy(buffer, data, length);
    buffer[length] = '\0';

    printf("Parsed data: %s\n", buffer);
}

int main() {
    char data[] = "Sample data for parsing";
    size_t length = strlen(data);

    parseData(data, length);

    return 0;
}