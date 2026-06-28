#include <stdio.h>
#include <string.h>

void parse_data(char* data, int length) {
    if (length > 0 && length < 100) {
        char buffer[length];
        strncpy(buffer, data, length);
        printf("Parsed data: %s\n", buffer);
    }
}

int main() {
    char data[200];
    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);
    parse_data(data, strlen(data));
    return 0;
}