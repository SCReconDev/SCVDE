#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void parseData(const char *data, int length) {
    if (length >= 0 && length <= MAX_LENGTH) {
        char buffer[MAX_LENGTH];
        strncpy(buffer, data, length);
        buffer[length] = '\0';
        printf("Parsed data: %s\n", buffer);
    } else {
        printf("Invalid length.\n");
    }
}

int main() {
    char data[MAX_LENGTH] = "Sample data";
    int length = strlen(data);
    parseData(data, length);
    return 0;
}