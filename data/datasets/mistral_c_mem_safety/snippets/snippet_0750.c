#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length > 0 && length <= 100) {
        char buffer[100];
        if (strlen(data) < length) {
            strncpy(buffer, data, length);
            buffer[length] = '\0';
            printf("Parsed data: %s\n", buffer);
        } else {
            printf("Data too long\n");
        }
    } else {
        printf("Invalid length\n");
    }
}

int main() {
    char data[100] = "Hello, World!";
    parse_data(data, strlen(data));
    return 0;
}